# See: https://rpm-software-management.github.io/rpm/manual/spec.html

%define         INSTALL_PREFIX /opt/Calendar
%define         USR_ROOT /user

Name:           calendar
Version:        1.0.25
Release:        1%{?dist}
Summary:        Rabbit remote control is is a cross-platform, multi-protocol remote control software.

License:        GPL-3.0
URL:            https://github.com/KangLin/Calendar
Source0:        Calendar.tar.gz

Vendor:         Kang Lin <kl222@126.com>

BuildRequires:  make git rpm-build rpmdevtools
BuildRequires:  gcc-c++
BuildRequires:  automake autoconf libtool gettext gettext-autopoint
BuildRequires:  cmake desktop-file-utils appstream curl wget
#BuildRequires: appstream

# Qt6
BuildRequires:  qt6-qttools-devel qt6-qtbase-devel qt6-qttranslations
BuildRequires:  qt6-qt5compat-devel qt6-qtmultimedia-devel qt6-qtscxml-devel
BuildRequires:  qt6-qtserialport-devel qt6-qtsvg-devel qt6-qtspeech-devel qt6-qtwebsockets-devel
BuildRequires:  qt6-qtwebengine-devel qt6-qtwebengine-devtools qt6-qtpositioning-devel qt6-qtwebchannel-devel

BuildRequires:  qtkeychain-qt6-devel qtermwidget-devel

BuildRequires:  libssh-devel libicu-devel lzo-devel libgcrypt-devel libcurl-devel
BuildRequires:  openssl-devel libpng-devel libjpeg-turbo-devel pixman-devel openh264-devel ffmpeg-free-devel
BuildRequires:  libvncserver-devel libpcap-devel
BuildRequires:  libwinpr-devel freerdp-devel freerdp fuse3-devel

# TigerVNC
BuildRequires:  libpciaccess-devel freetype-devel pam-devel
BuildRequires:  gnutls-devel nettle-devel gmp-devel
BuildRequires:  zlib-devel systemd-devel
# X11/graphics  dependencies
BuildRequires:  libXext-devel libX11-devel libXi-devel libXfixes-devel libXtst-devel
BuildRequires:  libXdamage-devel libXrandr-devel libXt-devel libXdmcp-devel
BuildRequires:  libXinerama-devel mesa-libGL-devel libxshmfence-devel
BuildRequires:  libdrm-devel mesa-libgbm-devel
BuildRequires:  libxkbfile-devel libXfont2-devel
BuildRequires:  mysql-devel

Requires: openssl libpng libjpeg-turbo pixman openh264 ffmpeg-free libssh libicu lzo libgcrypt
Requires: libvncserver freerdp-libs libwinpr libpcap libcurl
#freerdp fuse3
Requires: zlib gnutls nettle gmp pam 
Requires: qt6-qtbase qt6-qtbase-mysql qt6-qtbase-odbc qt6-qtbase-postgresql
Requires: qt6-qtmultimedia qt6-qt5compat qt6-qtscxml qt6-qtserialport qt6-qtsvg
Requires: qt6-qtwebengine qt6-qtpositioning qt6-qtwebchannel qt6-qtspeech
Requires: qtkeychain-qt6 qtermwidget qt6-qttranslations
Requires: mysql-libs

Requires: libXext libX11 libXi libXfixes libXtst
Requires: libXdamage libXrandr libXt libXdmcp
Requires: libXinerama mesa-libGL libxshmfence
Requires: libdrm mesa-libgbm
Requires: libxkbfile libXfont2

%description
Calendar using Qt
 Calendar

 Include:
   - Calendar
     - solar
     - lunar
   - Task
   - sticky

Author: Kang Lin <kl222@126.com>

Donation:

https://github.com/KangLin/RabbitCommon/raw/master/Src/Resource/image/Contribute.png

https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute.png

https://gitlab.com/kl222/RabbitCommon/-/raw/master/Src/Resource/image/Contribute.png

# 预备参数
%prep
%setup -q -n Calendar

%generate_buildrequires

%build
echo "-- RPM_BUILD_DIR: $RPM_BUILD_DIR"
echo "-- RPM_BUILD_ROOT: $RPM_BUILD_ROOT"
echo "-- RPM_SOURCE_DIR: $RPM_SOURCE_DIR"
echo "-- RPM_SPECPARTS_DIR: $RPM_SPECPARTS_DIR"
echo "-- pwd: `pwd`"

cmake . -B $RPM_BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=%{INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release \
    -DRabbitCommon_ROOT=${RabbitCommon_ROOT} \
    -DCMARK_SHARED=OFF \
    -DCMARK_TESTS=OFF \
    -DCMARK_STATIC=ON \
    -DWITH_CMARK=OFF \
    -DWITH_CMARK_GFM=ON \
    -DENABLE_UPDATE_TRANSLATIONS=ON \
    -DRABBIT_ENABLE_INSTALL_TARGETS=ON \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DINSTALL_QFtpServer=ON
cmake --build $RPM_BUILD_DIR --config Release --parallel $(nproc)

%install
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component DependLibraries \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Runtime \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Plugin \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Application \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}

#if [ -n "${INSTALL_DIR}" ]; then
#    SOURCE_DIR=${INSTALL_DIR}%{_libdir}
#    DEST_DIR=${RPM_BUILD_ROOT}%{INSTALL_PREFIX}%{_libdir}
#    # 复制 .so 库文件及其符号链接
#    find $SOURCE_DIR -name "*.so*" -exec cp -d {} $DEST_DIR \;
#fi

# 安装前需要做的任务，如：创建用户
%pre

# 安装后需要做的任务 如：自动启动的任务
%post
INSTALL_PREFIX=/opt/RabbitRemoteControl
USR_ROOT=/usr
mkdir -p $INSTALL_ROOT/log
chmod -R a+w $INSTALL_ROOT/log

if [ ! -d $INSTALL_ROOT/bin/log -a -d $INSTALL_ROOT/log ]; then
    ln -s $INSTALL_ROOT/log $INSTALL_ROOT/bin/log
fi
if [ -d $INSTALL_ROOT/etc ]; then
    chmod -R a+rw $INSTALL_ROOT/etc
fi

if [ ! -f $USR_ROOT/share/applications/io.github.KangLin.Calendar.desktop ]; then
    ln -s ${INSTALL_ROOT}/share/applications/io.github.KangLin.Calendar.desktop $USR_ROOT/share/applications/io.github.KangLin.Calendar.desktop
fi
if [ ! -d ~/.config/autostart ]; then
    mkdir -p ~/.config/autostart
    chmod 755 ~/.config/autostart
fi
if [ ! -f  ~/.config/autostart/io.github.KangLin.Calendar.desktop ]; then
    ln -s ${INSTALL_ROOT}/share/applications/io.github.KangLin.Calendar.desktop ~/.config/autostart/io.github.KangLin.Calendar.desktop
fi
if [ ! -f $USR_ROOT/share/pixmaps/io.github.KangLin.Calendar.png ]; then
    if [ ! -d $USR_ROOT/share/pixmaps ]; then
        mkdir -p $USR_ROOT/share/pixmaps
    fi
    ln -s ${INSTALL_ROOT}/share/pixmaps/io.github.KangLin.Calendar.png $USR_ROOT/share/pixmaps/io.github.KangLin.Calendar.png
fi
if [ ! -f $USR_ROOT/bin/rabbitcalendar ]; then
    ln -s $INSTALL_ROOT/bin/CalendarlApp $USR_ROOT/bin/rabbitcalendar
fi

if command -v update-mime-database >/dev/null 2>&1; then
    if [ -d $USR_ROOT/share/mime ]; then
        update-mime-database $USR_ROOT/share/mime/
    fi
fi
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database $USR_ROOT/share/applications/
fi

# 卸载前需要做的任务 如：停止任务
%preun

# 卸载后需要做的任务 如：删除用户，删除/备份业务数据
%postun
INSTALL_PREFIX=/opt/RabbitRemoteControl
USR_ROOT=/usr
rm -fr $INSTALL_ROOT/log $INSTALL_ROOT/bin/log
rm -fr ~/.config/autostart/io.github.KangLin.Calendar.desktop
rm -fr $USR_ROOT/share/applications/io.github.KangLin.Calendar.desktop
rm -fr /etc/ld.so.conf.d/Calendar.conf
rm -fr $USR_ROOT/share/pixmaps/io.github.KangLin.Calendar.png
rm -fr $USR_ROOT/bin/rabbitcalendar

if command -v update-mime-database >/dev/null 2>&1; then
    if [ -d $USR_ROOT/share/mime ]; then
        update-mime-database $USR_ROOT/share/mime/
    fi
fi
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database $USR_ROOT/share/applications/
fi

# 清除上次编译生成的临时文件
%clean

# 设置文件属性，包含编译文件需要生成的目录、文件以及分配所对应的权限
%files
%dir %{INSTALL_PREFIX}

%{INSTALL_PREFIX}/*

# 修改历史
%changelog
* %{build_time} Kang Lin <kl222@126.com> - %{version}
- Initial RPM package
