# 1. 让使用者输入文件名称,并取得 fileuser 这个变量;
echo -e "I will use 'touch' command to create 3 files."
read -p "Please input the filename what you want: " fileuser
# 2. 为了避免使用者随意按 Enter ,利用变量功能分析文件名是否有设定?
filename=${fileuser:-"filename"}
# 3. 开始利用 date 指令来取得所需要的档名了;
date1=`date --date='2 days ago' +%Y%m%d`
date2=`date --date='1 days ago' +%Y%m%d`
date3=`date +%Y%m%d`
file1="$filename""$date1"
file2="$filename""$date2"
file3="$filename""$date3"
# 4. 将档名建立吧!
touch $file1
touch $file2
touch $file3
