#include "simulate3d.h"

Simulate3d::Simulate3d(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(20);
    sphereMesh->setSlices(20);
    sphereMesh->setRadius(0.5);



    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(QColor(QRgb(0xa69929)));

    // Sphere
    m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);
    //m_sphereEntity->addComponent(sphereTransform);

    m_sphereEntity->setEnabled(true);

    qRegisterMetaType<Qt3DAnimation::QAbstractAnimationClip*>("Qt3DAnimation::QAbstractAnimationClip*");

    //show();

}

Simulate3d::~Simulate3d()
{
    delete m_rootEntity;
    delete m_sphereEntity;
}

void Simulate3d::show()
{
    auto animator = new Qt3DAnimation::QClipAnimator(m_sphereEntity);

    auto animationClip = new  Qt3DAnimation::QAnimationClip(animator);

    auto data = Qt3DAnimation::QAnimationClipData();

    // Add a channel for a Location animation
    auto location = Qt3DAnimation::QChannel(QLatin1String("Location"));

    auto locationX =Qt3DAnimation::QChannelComponent(QLatin1String("Location X"));
    locationX.appendKeyFrame(Qt3DAnimation::QKeyFrame({0.0f, 0.0f}));
    locationX.appendKeyFrame(Qt3DAnimation::QKeyFrame({2.0f, 2.0f}));

    auto locationY = Qt3DAnimation::QChannelComponent (QLatin1String("Location Y"));
    locationY.appendKeyFrame(Qt3DAnimation::QKeyFrame({0.0f, 0.0f}));
    locationY.appendKeyFrame(Qt3DAnimation::QKeyFrame({1.0f, 2.0f}));
    locationY.appendKeyFrame(Qt3DAnimation::QKeyFrame({2.0f, 0.0f}));

    auto locationZ = Qt3DAnimation::QChannelComponent(QLatin1String("Location Z"));
    locationZ.appendKeyFrame(Qt3DAnimation::QKeyFrame({0.0f, 0.0f},{-1.0f, 0.0f},{1.0f, 0.0f}));

    location.appendChannelComponent(locationX);
    location.appendChannelComponent(locationY);
    location.appendChannelComponent(locationZ);

    data.appendChannel(location);

    animationClip->setClipData(data);
    animationClip->setEnabled(true);

    animator->setClip(animationClip);

    // Sphere mesh transform
    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

    sphereTransform->setScale(1.3f);
    sphereTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DAnimation::QChannelMapping *m_mapping = new Qt3DAnimation::QChannelMapping;
    m_mapping->setChannelName("Location");
    m_mapping->setTarget(sphereTransform);
    m_mapping->setProperty("translation");

    Qt3DAnimation::QChannelMapper *m_channelMapper = new Qt3DAnimation::QChannelMapper;
    m_channelMapper->addMapping(m_mapping);
    //animator->setLoopCount(3);

    animator->setChannelMapper(m_channelMapper);




    m_sphereEntity->addComponent(sphereTransform);

    animator->setRunning(true);

    animator->start();

}
