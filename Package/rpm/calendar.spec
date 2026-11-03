# See: https://rpm-software-management.github.io/rpm/manual/spec.html
%define         INSTALL_PREFIX /opt/Calendar

Name:           rabbitcalendar
Version:        1.0.26
Release:        1%{?dist}
Summary:        Rabbit calendar is is a cross-platform calendar.

License:        GPL-3.0
URL:            https://github.com/KangLin/Calendar
Source0:        Calendar.tar.gz

Vendor:         Kang Lin <kl222@126.com>

BuildRequires:  make git rpm-build rpmdevtools
BuildRequires:  gcc-c++
BuildRequires:  automake autoconf libtool gettext gettext-autopoint
BuildRequires:  cmake desktop-file-utils appstream curl wget

# Qt6
BuildRequires:  qt6-qttools-devel qt6-qtbase-devel qt6-qttranslations
BuildRequires:  qt6-qt5compat-devel qt6-qtscxml-devel
BuildRequires:  qt6-qtsvg-devel qt6-qtspeech-devel

BuildRequires:  openssl-devel

BuildRequires:  mysql-devel

Requires: openssl

Requires: qt6-qtbase qt6-qtbase-mysql qt6-qtbase-odbc qt6-qtbase-postgresql
Requires: qt6-qt5compat qt6-qtscxml qt6-qttranslations
Requires: mysql-libs

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
    -DWITH_MEDIA_DEVICES=OFF \
    -DWITH_FILE_TRANSFER=OFF \
    -DWITH_WebEngineWidgets=OFF
cmake --build $RPM_BUILD_DIR --config Release --parallel $(nproc)

%install
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component DependLibraries \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Runtime \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}
cmake --install $RPM_BUILD_DIR --config Release --strip \
    --component Application \
    --prefix ${RPM_BUILD_ROOT}%{INSTALL_PREFIX}

# 安装前需要做的任务，如：创建用户
%pre

# 安装后需要做的任务 如：自动启动的任务
%post
INSTALL_PREFIX=/opt/Calendar
USER_ROOT=/usr
if [ -n "$INSTALL_PREFIX" -a -d $INSTALL_PREFIX/etc ]; then
    chmod -R a+rw $INSTALL_PREFIX/etc
fi
if [ ! -f ${USER_ROOT}/share/applications/io.github.KangLin.Calendar.desktop ]; then
    if [ -f ${INSTALL_PREFIX}/share/applications/io.github.KangLin.Calendar.desktop ]; then
      ln -s ${INSTALL_PREFIX}/share/applications/io.github.KangLin.Calendar.desktop \
        ${USER_ROOT}/share/applications/io.github.KangLin.Calendar.desktop
    fi
fi
#if [ ! -d ~/.config/autostart ]; then
#    mkdir -p ~/.config/autostart
#    chmod 755 ~/.config/autostart
#fi
#if [ ! -f  ~/.config/autostart/io.github.KangLin.Calendar.desktop ]; then
#    ln -s ${INSTALL_PREFIX}/share/applications/io.github.KangLin.Calendar.desktop \
#      ~/.config/autostart/io.github.KangLin.Calendar.desktop
#fi
if [ ! -f ${USER_ROOT}/share/pixmaps/io.github.KangLin.Calendar.png ]; then
    if [ ! -d ${USER_ROOT}/share/pixmaps ]; then
        mkdir -p ${USER_ROOT}/share/pixmaps
    fi
    if [ -f ${INSTALL_PREFIX}/share/pixmaps/io.github.KangLin.Calendar.png ]; then
        ln -s ${INSTALL_PREFIX}/share/pixmaps/io.github.KangLin.Calendar.png \
          ${USER_ROOT}/share/pixmaps/io.github.KangLin.Calendar.png
    fi
fi
if [ ! -f ${USER_ROOT}/bin/rabbitcalendar ]; then
    if [ -f $INSTALL_PREFIX/bin/CalendarlApp ]; then
        ln -s $INSTALL_PREFIX/bin/CalendarlApp ${USER_ROOT}/bin/rabbitcalendar
    fi
fi
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database ${USER_ROOT}/share/applications/
fi

# 卸载前需要做的任务 如：停止任务
%preun

# 卸载后需要做的任务 如：删除用户，删除/备份业务数据
%postun
INSTALL_PREFIX=/opt/Calendar
USER_ROOT=/usr
#rm -fr ~/.config/autostart/io.github.KangLin.Calendar.desktop
rm -fr ${USER_ROOT}/share/applications/io.github.KangLin.Calendar.desktop
rm -fr ${USER_ROOT}/share/pixmaps/io.github.KangLin.Calendar.png
rm -fr ${USER_ROOT}/bin/rabbitcalendar

if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database ${USER_ROOT}/share/applications/
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
