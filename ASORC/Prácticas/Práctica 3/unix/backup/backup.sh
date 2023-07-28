#!bin/bash
# backup file name of the absolute copy:
BACKUP_FILE_NAME_ABS='_Abs'
# backup file name of the differential copy:
BACKUP_FILE_NAME_DIFF='_Diff'
# Name of the directory to have the backup
DIR='/home/daniel/Documentos'
# Begin the script
#
. ~/.bash_profile
if [ $1 = "-d" ];then
 echo 'copia diferencial';
 DATE=`date +%d%m%y%H%M`
 ADD_TO_TAR='-N '$DATE
 TYPE=$BACKUP_FILE_NAME_DIFF;
else
 echo 'copia absoluta'
 DATE=''
 ADD_TO_TAR=''
 TYPE=$BACKUP_FILE_NAME_ABS;
fi

tar -cpvzf $DATE'_backup'$TYPE $DIR $ADD_TO_TAR
