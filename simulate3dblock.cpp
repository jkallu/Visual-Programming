#include "simulate3dblock.h"

Simulate3dBlock::Simulate3dBlock(int i):
    BlockIO (i, 2, 0, BlockItem::BlockType::Simulate)
{
    init();
}

void Simulate3dBlock::init()
{
    view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = createWindowContainer(view,this);

    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(100, 100));
    container->setMaximumSize(screenSize);

    //Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(new Qt3DAnimation::QAnimationAspect());

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 50.0f));
    cameraEntity->setUpVector(QVector3D(0, 0, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Simulate3d
    simulate3d = new Simulate3d(rootEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    // Create control widgets
    QCommandLinkButton *info = new QCommandLinkButton();
    info->setText(QStringLiteral("Qt3D ready-made meshes"));
    info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, "
                                             "cube, plane and sphere."));
    info->setIconSize(QSize(0,0));

    boxLayout->addWidget(container, 3, 0, 1, 2);
    lblData->setVisible(false);
    teData->setVisible(false);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Simulate Block");

    animator = new Qt3DAnimation::QClipAnimator(simulate3d->m_sphereEntity);
    animationClip = new  Qt3DAnimation::QAnimationClip(animator);
}

void Simulate3dBlock::setData(char *data)
{
    t_data.clear();
    x_data.clear();
    y_data.clear();
    z_data.clear();

    if(data == nullptr)
    {
        return;
    }
    Types type = Types::PACK_COUNT_MAX;
    size_t size_0 = 0, size_1 = 0;
    char *data_0 = nullptr, *data_1 = nullptr;

    getData(0, data, &type, &size_0, &data_0);
    getData(1, data, &type, &size_1, &data_1);
    qDebug() << "SIZE FROM GRAPH " << size_0 << " " << size_1 << endl;
    qDebug() << "type FROM GRAPH " << type << endl;
    createIOArray(0, 0, size_0);
    createIOArray(0, 1, size_1);
    size_t add = 0;
    if(type == Types::Pack_Int)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            int d;
            memcpy(&d, data_0 + add, sizeof (int));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (int);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            int d;
            memcpy(&d, data_1 + add, sizeof (int));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (int);
        }
    }
    else if(type == Types::Pack_Float)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            float d = 0;
            memcpy(&d, data_0 + i * sizeof (d), sizeof (d));
            in[0][i] = d;
            //qDebug() << i << " " << d << endl;
            flagIn[0] = true;
            add += sizeof (d);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            float d = 0;
            memcpy(&d, data_1 + add, sizeof (float));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (float);
        }
    }
    else if(type == Types::Pack_Double)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            double d;
            memcpy(&d, data_0 + add, sizeof (double));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (double);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            double d;
            memcpy(&d, data_1 + add, sizeof (double));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (double);
        }
    }


    show();
}

void Simulate3dBlock::show()
{
    auto data = Qt3DAnimation::QAnimationClipData();

    // Add a channel for a Location animation
    auto location = Qt3DAnimation::QChannel(QLatin1String("Location"));

    auto locationX =Qt3DAnimation::QChannelComponent(QLatin1String("Location X"));

    int size = getSize(0, 0);
    for(int i = 0; i < size; i++)
    {

        locationX.appendKeyFrame(Qt3DAnimation::QKeyFrame(QVector2D(in[0][i], in[1][i])));
    }

    auto locationY = Qt3DAnimation::QChannelComponent (QLatin1String("Location Y"));
    locationY.appendKeyFrame(Qt3DAnimation::QKeyFrame(QVector2D(in[0][0], 0.0)));
    locationY.appendKeyFrame(Qt3DAnimation::QKeyFrame(QVector2D(in[0][size - 1], 0.0)));

    auto locationZ = Qt3DAnimation::QChannelComponent(QLatin1String("Location Z"));
    locationZ.appendKeyFrame(Qt3DAnimation::QKeyFrame(QVector2D(in[0][0], 0.0)));
    locationZ.appendKeyFrame(Qt3DAnimation::QKeyFrame(QVector2D(in[0][size - 1], 0.0)));

    location.appendChannelComponent(locationX);
    location.appendChannelComponent(locationY);
    location.appendChannelComponent(locationZ);

    data.appendChannel(location);

    animationClip->setClipData(data);
    animationClip->setEnabled(true);

    animator->setClip(animationClip);

    // Sphere mesh transform
    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

    Qt3DAnimation::QChannelMapping *m_mapping = new Qt3DAnimation::QChannelMapping;
    m_mapping->setChannelName("Location");
    m_mapping->setTarget(sphereTransform);
    m_mapping->setProperty("translation");

    Qt3DAnimation::QChannelMapper *m_channelMapper = new Qt3DAnimation::QChannelMapper;
    m_channelMapper->addMapping(m_mapping);
    animator->setLoopCount(3);

    animator->setChannelMapper(m_channelMapper);




    simulate3d->m_sphereEntity->addComponent(sphereTransform);

    animator->setRunning(true);

    animator->start();

}
