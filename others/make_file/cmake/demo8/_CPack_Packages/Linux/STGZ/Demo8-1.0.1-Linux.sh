#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --prefix=dir      directory in which to install
  --include-subdir  include the Demo8-1.0.1-Linux subdirectory
  --exclude-subdir  exclude the Demo8-1.0.1-Linux subdirectory
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "Demo8 Installer Version: 1.0.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
The MIT License (MIT)
Copyright (c) 2013 Joseph Pan(http://hahack.com)
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the Demo8 will be installed in:"
    echo "  \"${toplevel}/Demo8-1.0.1-Linux\""
    echo "Do you want to include the subdirectory Demo8-1.0.1-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/Demo8-1.0.1-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

tail $use_new_tail_syntax +158 "$0" | gunzip | (cd "${toplevel}" && tar xf -) || cpack_echo_exit "Problem unpacking the Demo8-1.0.1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� Q�dX �YpT���y�M�*���%� a��l~�Q���@ ����x�}�>��[߾�ǆ�F�L:�:S�VG�u:�vt:���iq� �БiѡUFZ�YJ�q�:tݞs�}��$Pf�67ܽ����s����x8��(U�*&��W[]-b	�Y2�?�7���~����D����2S*i�:tE�4�R�����$��X�w�������Q����������X�����w5:�L���_U%QEd˟ҕ��%U�'E9��a��Τء�⺔��+�Q:Ը"6)]��!Զ��u���~Ek���ټ
��b�є$U�������M�@��]�H�è~qq���T����7��խ��wT���?���R6�K��'�b3p������� �篞WS;~��E��v�C�+�&-�_�Vv��S�j��#��8�.'�JQ���#�ŕ�1{a�L%Q;���7%�����a�r��_]���E�����v�/�:.c� ��US�����$}g����wW�������������X�o"���wA~���Q^Q
�"A�}��ZUqq�ώ�g~����A_N��P�R�˕���e����Yd��>J���<B��PɁ���P�����R���g�<s��hh���|:4��Jʆ�����Pi�y�<}_�pT(G���l6�U�Ϝ�yk ��ɱ�����nYc�qֲU�g�A�������j}AqVx��e��ϭ��M�7��ːۡ4tVF�/]�y���7"2�'�P�1"�uu�M�q�P��m.l��W�Sn��<����j(^΀\d��i!����q��.�'�Lys8�r8���~���u�oL�B����w�N8����-}3qkF�Y���} ��}��q��d��ĭ��s&k�@>�Zy�V6H��AOt��1��
�o��q�q�	3	<�dc�AM��"2�����?>կ��K�� ���`���m��t���G𠅯,a�A"���En!7� y�=��L@F��vmK��^�C��8�CY¶�/���LmN)�Ӻ'���.~�2+Z����|h�����tc�-���� �~��o�r�G��	L=A��*�S�ޤ��7��W>���i�M+Om����_|��#޲G� o����;��5��ڇ?�.Y���_������ç��}�1���7�ݿ���W�>�R2�oO�==�����1����,�S!��c����?���q�ow���I�sq��>��{qr����0�"�q��}���z2�|��J��=�t?�g-��m���;�<	��9�J�a�}1i@�о���&z��#s��c�L�d�0�=��]C��V)iDԸ�J*�HI�f����D����Ɛ�d5nք�)�C���J��IDg��m%kChl%!RGB�n�zf�ۤ6�SM����I%I��474J/]^7ݕn���ɕ�|�KUu2��-�O��M��}ʉ �`	����!,aq.`	�"������������`���~Pي3|_d+P:�G�;~t��D�w��Q[�x�0�Qkt:�/R�Gq��{��؋�,�������_�g�V�k��^��[�!��&� .��Cצ�vb�ށ_L#��1t�{�hf��������?��s��1����%���Ew���!ܠ�����=>�î�*;�A��=s���o
�6����׿�x6w�<��9lL}���F�5�.{⭁���r��}p�k҃MV���H׹w7��?�� ���M�ԲC��h��!}f��٬���n0�������#F(��x��1k=��P(P���� ���K�tYyf>Ȃ�{0�2^	����.l��/�Z�mo�d�ͦ{7���t�����JT��/l/������g�����;�X��`Yf4�K�Y���zcא�w�l�9��#}/�����p��0��}�<{c��0�P���e��H�z�ʹ����%��-/f���y!{�� �S�q�Qz�I@�Y@�2{{T$����\��x+"�d}R�T����n.�+�U�vq�"����.j��"��"�"]�wzER�)n9���1kyֺf,�C����,B[
˿�SPvC9���Cm���q�(��.vהA���l6��)��SJV\7�v��7/�#P�]<�K oY�o����q7L.�mx��ט.|D�G�>h
�%��%������?��jѽ잨L�̓�8��r{��{з�Tp
#θ��_K�Bj���J�3ѐ��K�V��%�1�if�4�̷{d���w!�s~^a�a}E1p=��.��s��x;�)oTNF�7�3�Yi茳�O!�,�8���(<��D.ܣD�]�R�hD�S�64=	�XqX���.5��}�?L�%�dƎ��4����b{�L��?�0_q�W�g�LfL��s8��s\��7�����E���<���]bF��6vF�繲��cg��&�>P�x?\�E��I���%���-�8�z1u�@��EB�M`�����I`vD��3q;I>"����-
c�5,�~��L��J9v�G�l�1�GY��c��u��%�}�~�Y�%G�=f��7���ǜ�C\7��=
�$Y�oH�/'�7:_8��^�����[������ѷi{�Zp(��E��'G������ɩ�����S�c��=b���{Z<�x�G�p���"��9ϑ�8g��%�H��gj�ؑO.�w,Ǌ|bB;CH>ҹ<G3��4��lԕi�f��i�f�M�EB�h6�M9��2��b��9z�p�I� ���,�w&a���Y����Q�;G�S����<.{Ф�Rғ��%.���;���s*G�H���-̓&=�XS���Ht��|�n�R���.�d���e������I��~���%Nc`�E߯�|���|[����~�.%'��@�̾����p��AOv�ǋ��V���A���|	h�2?1Ѓ�L����+��.X���W]��w������I>p��6�,8�6|pY�(n7�Ņ�����un{���m�Wi�E���8�
��m�mw��N݈�đ�n{�Q[����q��8��C����n{܉T��:"v��U꼺������(VQ߲����º�z5�c1KP�@u�Hutx�D�׵�I-�k��XQ��Zј#����ou��y�DL1��~�?iRgLk�c�%9��0?2����i�	�j����կ�(Tc~��s�0 }u���D#a����NՒ���-�3�ajM]��S1�DX2�����#�L@���#���&E�x$�ؕsEM���_��ho�y�ZZ�[�֥K׆�I��ZB҈��%��B�K��Cp�����~I��q@{�qD���t��!���!P�?�X�U.8mz���4���xOߨ���e 4  