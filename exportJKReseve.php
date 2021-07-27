/*
* @Author: your name
* @Date: 2021-07-22 16:05:55
* @LastEditTime: 2021-07-22 16:05:55
* @LastEditors: Please set LastEditors
* @Description: In User Settings Edit
* @FilePath: /algorithm/exportJKReseve.php
*/
ipArr=("100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60" "100.95.205.60")
portArr=("4020" "4317" "3909" "4185" "3944" "4177" "4142" "3830" "4167" "3718")
tableName="tbUserBookInfoByAcc"
dbName="20190916_feeling_Willsonwang_"
echo "" > wxAccount.txt
for((i=0;i<10;i++)) do #sql="select AccountID from ${tableName} where AccountStyle='wx' and PlatID='WEIBO' and RealChannel<>'WEIBO'  and BookTime < '2019-10-22 11:59:59'" sql="select BookCertificate from ${tableName} where AccountStyle='wx'" #sql="select BookCertificate from ${tableName} where AccountStyle='qq'" echo ${ipArr[$i]} ${portArr[$i]} ${dbName} for((j=0;j<10;j++)) do mysql -A -h${ipArr[$i]} -P${portArr[$i]} -Ddb${dbName}$j -ucdb_lolact_usr -pcdb_lolact_pwd -N -e"${sql}">> wxAccount.txt
  done
  done
