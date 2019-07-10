FROM ubuntu
MAINTAINER Jinesh Kallunkathariyil <jinesh.kallunkathariyil@gmail.com>

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8

#RUN sed -i 's/ universe/ universe multiverse/' /etc/apt/sources.list
RUN apt update &&                  \
    apt upgrade -y &&              \
    apt dist-upgrade -y &&         \
    apt install -y                 \
        git                        \
        wget                       \
        xvfb                       \
        flex                       \
        dh-make                    \
        debhelper                  \
        checkinstall               \
        fuse                       \
        snapcraft                  \
        bison                      \
        libxcursor-dev             \
        libxcomposite-dev          \
        software-properties-common \
        build-essential            \
        libssl-dev                 \
        libxcb1-dev                \
        libx11-dev                 \
        libgl1-mesa-dev            \
        libudev-dev                \
        qt5-default                \
        qtbase5-private-dev        \
 	      libqt5svg5-dev             \
        qtcreator			             \
        qt3d5*			               \
        libgsl23 			             \
        libgslcblas0               \ 
        libgsl-dbg 		        	   \
        libgsl-dev               &&\
        apt clean

WORKDIR /home/root/

CMD ["/bin/bash"]


RUN ln -s /usr/lib/x86_64-linux-gnu/pkgconfig/Qt5Gui.pc /usr/lib/x86_64-linux-gnu/pkgconfig/QtGui.pc 

RUN ln -s /usr/lib/x86_64-linux-gnu/pkgconfig/Qt5Core.pc /usr/lib/x86_64-linux-gnu/pkgconfig/QtCore.pc


RUN ln -s /usr/lib/x86_64-linux-gnu/pkgconfig/Qt5Network.pc /usr/lib/x86_64-linux-gnu/pkgconfig/QtNetwork.pc


RUN ln -s /usr/lib/x86_64-linux-gnu/pkgconfig/Qt5Widgets.pc /usr/lib/x86_64-linux-gnu/pkgconfig/QtWidgets.pc 

RUN ln -s /usr/lib/x86_64-linux-gnu/pkgconfig/Qt5Svg.pc /usr/lib/x86_64-linux-gnu/pkgconfig/QtSvg.pc

RUN export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/x86_64-linux-gnu/pkgconfig/

RUN export QT_CFLAGS="-DQT_GUI_LIB -DQT_CORE_LIB -DQT_NETWORK_LIB -DQT_WIDGETS_LIB -DQT_SVG_LIB -I/usr/include/x86_64-linux-gnu /qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtNetwork -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64 -linux-gnu/qt5/QtSvg -I/usr/include/x86_64-linux-gnu/qt5"

RUN wget https://downloads.sourceforge.net/project/gnuplot/gnuplot/5.2.7/gnuplot-5.2.7.tar.gz
RUN tar -xzf gnuplot-5.2.7.tar.gz
RUN rm gnuplot-5.2.7.tar.gz
RUN cd gnuplot-5.2.7/
RUN pwd
RUN ./configure --with-qt=qt5
RUN make
RUN make install

