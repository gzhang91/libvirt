dnl The libxml-2.0 library
dnl
dnl Copyright (C) 2016 Red Hat, Inc.
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public
dnl License as published by the Free Software Foundation; either
dnl version 2.1 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Lesser General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public
dnl License along with this library.  If not, see
dnl <http://www.gnu.org/licenses/>.
dnl

AC_DEFUN([LIBVIRT_ARG_LIBXML], [
  LIBVIRT_ARG_WITH([LIBXML], [libxml-2.0 location], [check])
])

AC_DEFUN([LIBVIRT_CHECK_LIBXML], [
  LIBXML_REQUIRED="2.9.1"

  LIBVIRT_CHECK_PKG([LIBXML], [libxml-2.0], [$LIBXML_REQUIRED])

  if test "$with_libxml" = "no" ; then
    AC_MSG_ERROR([libxml2 >= $LIBXML_REQUIRED is required for libvirt])
  fi
])

AC_DEFUN([LIBVIRT_RESULT_LIBXML], [
  LIBVIRT_RESULT_LIB([LIBXML])
])
