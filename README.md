# Project for export data from Honeywell Experion PKS database

- Check IP addresses before run program.
- For compiling use Microsoft Visual Studio 2008

Default run command exmple:

- hwoxcol.exe -h 10.1.1.103 -rhep 191.168.1.100:3000/upload -start template_for_gen.csv 10 000

Structure:

- hwoxcol.exe -h <main_server_ip> -rhep <remote_reciever_web_host_address> -start <template_csv_file>

Template csv file example:

|TAGNAME | POINT_ID | PARAM_ID |
|-|-|-|
| BUBFLW2S | 6321|	32765 |
| XAGD003_03 |	1001 |	32759
| ZICBI032	| 3368 |	32763 |
| ZLHLBI309 |	194 |	1|
| OPFD044 |	3011	| 32761|
