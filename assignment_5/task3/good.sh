#!/bin/bash 
cat << "EOF" | openssl dgst -sha256 > DIGEST 

    %Ce��l���Ȭ�忯���[Q#cnA!O��� ����O�s�Ht\�G~�Zr$��㗁y�FT���Y����(9��jƗhf� Y�����p]����ʝf����<�S�����
6-�N��2Q
EOF
 
digest=$(cat DIGEST | cut -c10- )
a="47ffb441d00bcd556f48b2b56ad71532e6cc0a3e2555bce751048b0ebabc06c9"
if [ "$digest" == "$a" ]
then
 echo "I mean no harm."
else
 echo "Your computer is hacked!"
fi
