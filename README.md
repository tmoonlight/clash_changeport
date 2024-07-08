clash端口自动变更工具，想要定时变更，可以将以下脚本加到crontab里

步骤：
crontab -e

增加一行：
0 */4 * * * /root/clash_cp
