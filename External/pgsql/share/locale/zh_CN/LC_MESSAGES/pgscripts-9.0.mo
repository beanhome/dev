��    �      ,  �   <
      �  K   �       f     
   �  >   �  >   �  =     -   I  C   w  A   �     �  #        :  (   U     ~  <   �  9   �  6     H   I  E   �  B   �  9     C   U  9   �  4   �  E     =   N  .   �  ;   �  E   �  :   =  5   x  7   �  9   �  7      4   X  L   �  J   �  5   %  2   [  C   �  7   �  2   
  2   =  J   p  :   �  5   �  G   ,  0   t  <   �  0   �  M     J   a  G   �  4   �  H   )  E   r  9   �  v   �  <   i  I   �  @   �  5   1  4   g  1   �  ;   �  5   
  6   @  3   w  4   �  =   �  8     8   W  8   �  2   �  9   �  6   6  >   m     �  /   �  <   �  #   %   #   I   ?   m   %   �   #   �      �   3   !  &   K!  5   r!  E   �!  I   �!  5   8"  I   n"  5   �"  E   �"  F   4#  @   {#  >   �#  4   �#  D   0$     u$  *   �$  8   �$  6   �$  %   .%  (   T%  (   }%  8   �%  #   �%      &     $&  8   D&  4   }&  $   �&     �&  ,   �&  ,   $'  ;   Q'  9   �'     �'     �'     �'     (  *    (  8   K(  ,   �(  8   �(  #   �(  G   )  4   V)     �)  )   �)  7   �)     
*     *  !   -*  +   O*     {*     �*     �*     �*     �*     �*  
   +     +     )+     F+  '   [+  "   �+  2   �+  7   �+     ,  &   ,     A,     I,     K,     N,  :   ],     �,     �,  ]  �,  >   �-     ;.  `   K.  	   �.  L   �.  H   /  K   L/  .   �/  <   �/  :   0     ?0  -   ^0      �0  ,   �0     �0  F   �0  C   ?1  @   �1  C   �1  @   2  =   I2  A   �2  8   �2  /   3  /   23  >   b3  2   �3  /   �3  2   4  ;   74  5   s4  J   �4  7   �4  ;   ,5  2   h5  /   �5  G   �5  G   6  7   [6  5   �6  E   �6  ;   7  5   K7  G   �7  H   �7  >   8  9   Q8  8   �8  7   �8  8   �8  J   59  D   �9  A   �9  >   :  /   F:  \   v:  Y   �:  @   -;  p   n;  A   �;  G   !<  ;   i<  B   �<  ;   �<  8   $=  5   ]=  /   �=  ?   �=  4   >  >   8>  >   w>  <   �>  F   �>  5   :?  5   p?  :   �?  7   �?  A   @     [@  3   g@  B   �@  '   �@  *   A  6   1A  6   hA  '   �A  $   �A  -   �A  +   B  A   FB  D   �B  M   �B  D   C  M   `C  J   �C  S   �C  J   MD  =   �D  ;   �D  A   E  D   TE  #   �E  #   �E  =   �E  /   F      OF  #   pF  '   �F  *   �F     �F     G     #G  7   AG  6   yG     �G     �G  &   �G  &   H  =   4H  ;   rH     �H     �H     �H  )   �H  3   I  B   FI  /   �I  K   �I      J  >   &J  1   eJ     �J  #   �J  =   �J     K     (K     ?K  &   \K     �K      �K     �K     �K     �K     �K     L     L     )L     @L      ML  "   nL  %   �L  ,   �L     �L  *   �L     M     ,M     .M     1M  0   ?M     pM     rM        W   s   a   !   �   %      X      �   j       C   ~         l   o   �   ^   :   �       e               u   �       f   V          �   v      <   c   E   
   �       R   �   �   ,       )   g       K   �               D                     S       i      	   _       9   N   �           J   2   �       \   h      >   m   y   ?              /         $                     0           -   �       1   .       �   (   �   F               `           �   8   x   �      H       @           I   �       �   �       �       Z       &          {   �       ]              '   A       n   G   Y   �   |   }       �   �   M   �       *      =   U   t   d       T      Q          �   #   �      P   O   r   B   k   4   +      ;   w       �   p   b               7   q       L   �   "               z               �   �   �       �   �       [   5       6   3       
By default, a database with the same name as the current user is created.
 
Connection options:
 
If one of -d, -D, -r, -R, -s, -S, and ROLENAME is not specified, you will
be prompted interactively.
 
Options:
 
Read the description of the SQL command CLUSTER for details.
 
Read the description of the SQL command REINDEX for details.
 
Read the description of the SQL command VACUUM for details.
 
Report bugs to <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      LC_COLLATE setting for the database
       --lc-ctype=LOCALE        LC_CTYPE setting for the database
   %s [OPTION]... DBNAME
   %s [OPTION]... LANGNAME [DBNAME]
   %s [OPTION]... [DBNAME]
   %s [OPTION]... [DBNAME] [DESCRIPTION]
   %s [OPTION]... [ROLENAME]
   --help                          show this help, then exit
   --help                       show this help, then exit
   --help                    show this help, then exit
   --version                       output version information, then exit
   --version                    output version information, then exit
   --version                 output version information, then exit
   -D, --no-createdb         role cannot create databases
   -D, --tablespace=TABLESPACE  default tablespace for the database
   -E, --encoding=ENCODING      encoding for the database
   -E, --encrypted           encrypt stored password
   -F, --freeze                    freeze row transaction information
   -I, --no-inherit          role does not inherit privileges
   -L, --no-login            role cannot login
   -N, --unencrypted         do not encrypt stored password
   -O, --owner=OWNER            database user to own the new database
   -P, --pwprompt            assign a password to new role
   -R, --no-createrole       role cannot create roles
   -S, --no-superuser        role will not be superuser
   -T, --template=TEMPLATE      template database to copy
   -U, --username=USERNAME      user name to connect as
   -U, --username=USERNAME   user name to connect as
   -U, --username=USERNAME   user name to connect as (not the one to create)
   -U, --username=USERNAME   user name to connect as (not the one to drop)
   -W, --password               force password prompt
   -W, --password            force password prompt
   -Z, --analyze-only              only update optimizer statistics
   -a, --all                       vacuum all databases
   -a, --all                 cluster all databases
   -a, --all                 reindex all databases
   -c, --connection-limit=N  connection limit for role (default: no limit)
   -d, --createdb            role can create new databases
   -d, --dbname=DBNAME             database to vacuum
   -d, --dbname=DBNAME       database from which to remove the language
   -d, --dbname=DBNAME       database to cluster
   -d, --dbname=DBNAME       database to install language in
   -d, --dbname=DBNAME       database to reindex
   -e, --echo                      show the commands being sent to the server
   -e, --echo                   show the commands being sent to the server
   -e, --echo                show the commands being sent to the server
   -f, --full                      do full vacuuming
   -h, --host=HOSTNAME          database server host or socket directory
   -h, --host=HOSTNAME       database server host or socket directory
   -i, --index=INDEX         recreate specific index only
   -i, --inherit             role inherits privileges of roles it is a
                            member of (default)
   -i, --interactive         prompt before deleting anything
   -l, --list                show a list of currently installed languages
   -l, --locale=LOCALE          locale settings for the database
   -l, --login               role can login (default)
   -p, --port=PORT              database server port
   -p, --port=PORT           database server port
   -q, --quiet                     don't write any messages
   -q, --quiet               don't write any messages
   -r, --createrole          role can create new roles
   -s, --superuser           role will be superuser
   -s, --system              reindex system catalogs
   -t, --table='TABLE[(COLUMNS)]'  vacuum specific table only
   -t, --table=TABLE         cluster specific table only
   -t, --table=TABLE         reindex specific table only
   -v, --verbose                   write a lot of output
   -v, --verbose             write a lot of output
   -w, --no-password            never prompt for password
   -w, --no-password         never prompt for password
   -z, --analyze                   update optimizer statistics
 %s (%s/%s)  %s cleans and analyzes a PostgreSQL database.

 %s clusters all previously clustered tables in a database.

 %s creates a PostgreSQL database.

 %s creates a new PostgreSQL role.

 %s installs a procedural language into a PostgreSQL database.

 %s reindexes a PostgreSQL database.

 %s removes a PostgreSQL database.

 %s removes a PostgreSQL role.

 %s removes a procedural language from a database.

 %s: "%s" is not a valid encoding name
 %s: cannot cluster a specific table in all databases
 %s: cannot cluster all databases and a specific one at the same time
 %s: cannot reindex a specific index and system catalogs at the same time
 %s: cannot reindex a specific index in all databases
 %s: cannot reindex a specific table and system catalogs at the same time
 %s: cannot reindex a specific table in all databases
 %s: cannot reindex all databases and a specific one at the same time
 %s: cannot reindex all databases and system catalogs at the same time
 %s: cannot use the "freeze" option when performing only analyze
 %s: cannot use the "full" option when performing only analyze
 %s: cannot vacuum a specific table in all databases
 %s: cannot vacuum all databases and a specific one at the same time
 %s: clustering database "%s"
 %s: clustering of database "%s" failed: %s %s: clustering of table "%s" in database "%s" failed: %s %s: comment creation failed (database was created): %s %s: could not connect to database %s
 %s: could not connect to database %s: %s %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: creation of new role failed: %s %s: database creation failed: %s %s: database removal failed: %s %s: language "%s" is already installed in database "%s"
 %s: language "%s" is not installed in database "%s"
 %s: language installation failed: %s %s: language removal failed: %s %s: missing required argument database name
 %s: missing required argument language name
 %s: only one of --locale and --lc-collate can be specified
 %s: only one of --locale and --lc-ctype can be specified
 %s: out of memory
 %s: query failed: %s %s: query was: %s
 %s: reindexing database "%s"
 %s: reindexing of database "%s" failed: %s %s: reindexing of index "%s" in database "%s" failed: %s %s: reindexing of system catalogs failed: %s %s: reindexing of table "%s" in database "%s" failed: %s %s: removal of role "%s" failed: %s %s: still %s functions declared in language "%s"; language not removed
 %s: too many command-line arguments (first is "%s")
 %s: vacuuming database "%s"
 %s: vacuuming of database "%s" failed: %s %s: vacuuming of table "%s" in database "%s" failed: %s Are you sure? Cancel request sent
 Could not send cancel request: %s Database "%s" will be permanently removed.
 Enter it again:  Enter name of role to add:  Enter name of role to drop:  Enter password for new role:  Name Password encryption failed.
 Password:  Passwords didn't match.
 Please answer "%s" or "%s".
 Procedural Languages Role "%s" will be permanently removed.
 Shall the new role be a superuser? Shall the new role be allowed to create databases? Shall the new role be allowed to create more new roles? Trusted? Try "%s --help" for more information.
 Usage:
 n no out of memory
 pg_strdup: cannot duplicate null pointer (internal error)
 y yes Project-Id-Version: pgscripts (PostgreSQL 9.0)
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-10-01 14:40+0000
PO-Revision-Date: 2010-10-01 12:52+0800
Last-Translator: Weibin <ssmei_2000@yahoo.com>
Language-Team: Chinese (Simplified)
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 
默认情况下, 以当前用户的用户名创建数据库.
 
联接选项:
 
如果 -d, -D, -r, -R, -s, -S 和 ROLENAME 一个都没有指定,将使用交互式提示
你.
 
选项:
 
阅读 SQL 命令 CLUSTER 的描述信息, 以便获得更详细的信息.
 
阅读SQL命令REINDEX的描述信息, 以便获得更详细的信息.
 
阅读 SQL 命令 VACUUM 的描述信息, 以便获得更详细的信息.
 
臭虫报告至 <pgsql-bugs@postgresql.org>.
       --lc-collate=LOCALE      数据库的LC_COLLATE设置
       --lc-ctype=LOCALE        数据库的LC_CTYPE设置
   %s [选项]... 数据库名
   %s [选项]... 语言名称 [数据库名]
   %s [选项]... [数据库名]
   %s [选项]... [数据库名称] [描述]
   %s [选项]... [用户名]
   --help                          显示此帮助信息, 然后退出
   --help                       显示此帮助信息, 然后退出
   --help                    显示此帮助信息, 然后退出
   --versoin                       输出版本信息, 然后退出
   --versoin                    输出版本信息, 然后退出
   --version                 输出版本信息, 然后退出
   -D, --no-createdb         此角色不可以创建新数据库
   -D, --tablespace=TABLESPACE  数据库默认表空间
   -E, --encoding=ENCODING      数据库编码
   -E, --encrypted           口令加密存储
   -F, --freeze                    冻结记录的事务信息
   -I, --no-inherit          角色不继承权限
   -L, --no-login            角色不能登录
   -N, --unencrypted         口令不加密存储
   -O, --owner=OWNER            新数据库的所属用户
   -P, --pwprompt            给新角色指定口令
   -R, --no-createrole       这个角色没有创建其它角色的权限
   -S, --no-superuser       角色不能是超级用户
   -T, --template=TEMPLATE      要拷贝的数据库模板
   -U, --username=USERNAME      联接的用户名
   -U, --username=USERNAME   联接的用户名
   -U, --username=USERNAME   联接用户 (不是要创建的用户名)
   -U, --username=USERNAME   联接用户 (不是要删除的用户名)
   -W, --password              强制提示输入口令
   -W, --password            强制提示输入口令
   -z, --analyze-only               只更新优化器的统计信息
   -a, --all                       清理所有的数据库
   -a, --all                 对所有数据库建簇
   -a, --all                 对所有数据库进行重建索引操作
   -c, --connection-limit=N  角色的连接限制(缺省: 没有限制)
   -d, --createdb            此角色可以创建新数据库
   -d, --dbname=DBNAME             清理数据库 DBNAME
   -d, --dbname=DBNAME       要删除语言的数据库
   -d, --dbname=DBNAME       对数据库 DBNAME 建簇
   -d, --dbname=DBNAME       要安装语言的数据库
   -d, --dbname=数据库名称       对数据库中的索引进行重建
   -e, --echo                      显示发送到服务端的命令
   -e, --echo                   显示发送到服务端的命令
   -e, --echo                显示发送到服务端的命令
   -f, --full                      完全清理
   -h, --host=HOSTNAME          数据库服务器所在机器的主机名或套接字目录
   -h, --host=HOSTNAM        数据库服务器所在机器的主机名或套接字目录
   -I, --index=索引名称       仅重新创建指定的索引
   -i, --inherit            角色能够继承它所属角色的权限
                   （这是缺省情况)
   -i, --interactive         删除任何东西之前给予提示
   -l, --list                显示当前已经安装了的语言列表
   -O, --owner=OWNER            新数据库的所属用户
   -l, --login              角色能够登录(这是缺省情况)
   -p, --port=PORT              数据库服务器端口号
   -p, --port=PORT           数据库服务器端口号
   -q, --quiet                     不写任何信息
   -q, --quiet               不写任何信息
   -r, --createrole        这个角色可以创建新的角色
   -s, --superuser          角色将是超级用户
   -s, --system              对系统视图重新创建索引
   -t, --table='TABLE[(COLUMNS)]'  只清理指定的表 TABLE
   -t, --table=TABLE         只对指定的表 TABLE 建簇
   -t, --table=表名        只对指定的表TABLE重新创建索引
   -v, --verbose                   写大量的输出
   -v, --verbose                   写大量的输出
   -w, --no-password           永远不提示输入口令
   -w, -no-password         永远不提示输入口令
   -z, --anaylze                   更新优化器的统计信息
 %s (%s/%s)  %s 清理并且优化一个 PostgreSQL 数据库.

 %s 对一个数据库中先前已经建过簇的表进行建簇.

 %s 创建一个 PostgreSQL 数据库.

 %s 创建一个新的 PostgreSQL 用户.

 %s 安装一个过程语言进 PostgreSQL 数据库.

 %s  对一个PostgreSQL 数据库重新创建索引.

 %s 删除一个 PostgreSQL 数据库.

 %s 删除一个 PostgreSQL 用户.

 %s 从数据库中删除一个过程语言.

 %s: "%s" 不是一个有效的编码名称
 %s: 无法在所有数据库中对一个指定的表进行建簇
 %s: 无法对所有数据库和一个指定的数据库同时建簇
 %s: 无法对一个指定索引和系统视图同时进行索引重建操作
 %s: 无法在所有数据库中对一个指定的索引进行重建
 %s: 无法对一张指定的表和系统视图同时进行索引重建操作
 %s: 无法在所有数据库中对一张指定表上的索引进行重建
 %s: 无法对所有数据库和一个指定的索引同时进行索引重建操作
 %s: 无法对所有数据库和系统目录同时进行索引重建操作
 %s: 当只执行分析的时候，无法使用选项"freeze"
 %s: 在只执行分析的时候，无法使用选项"full"
 %s: 无法在所有数据库中对一个指定的表进行清理
 %s: 无法对所有数据库和一个指定的数据库同时清理
 %s: 对数据库 "%s" 进行建簇
 %s: 数据库 "%s" 建簇失败: %s %1$s: 在数据库 "%3$s" 中的表 "%2$s" 建簇失败: %4$s %s: 创建注释失败 (数据库已创建): %s %s: 无法联接到数据库 %s
 %s: 无法联接到数据库 %s: %s %s: 无法获取当前用户名称: %s
 %s: 无法获得当前用户的信息: %s
 %s: 创建新用户失败: %s %s: 创建数据库失败: %s %s: 数据库删除失败: %s %1$s: 数据库 "%3$s" 中已经安装了语言 "%2$s"
 %1$s: 数据库 "%3$s" 中, 没有安装语言 "%2$s"
 %s: 语言安装失败: %s %s: 语言删除失败: %s %s: 缺少需要的数据库名参数
 %s: 缺少要求的语言名称参数
 %s: 只能指定--locale和--lc-collate这两个选项之一
 %s: 只能指定--locale和--lc-ctype这两个选项之一
 %s: 内存溢出
 %s: 查询失败: %s %s: 查询是: %s
 %s: 对数据库 "%s" 重新创建索引
 %s: 在数据库"%s"上重新创建索引失败: %s %1$s: 在数据库"%3$s"中对索引"%2$s"重新创建失败: %4$s %s: 对目录视图重新创建索引失败: %s %1$s: 在数据库"%3$s"中对表"%2$s"上的索引重新创建失败: %4$s %s: 删除用户 "%s" 失败: %s %s: 函数 %s 是用语言 "%s" 声明的; 语言未被删除
 %s: 太多的命令行参数 (第一个是 "%s")
 %s: 清理数据库 "%s"
 %s: 数据库 "%s" 清理失败: %s %1$s: 在数据库 "%3$s" 中的表 "%2$s" 清理失败: %4$s 您确定吗? (y/n)  取消发送的请求
 无法发送取消请求: %s 数据库 "%s" 将被永久的删除.
 再输入一遍:  输入要增加的角色名称:  输入要删除的用户名:  为新角色输入的口令:  名字 密码加密失败.
 口令:  口令不匹配.
 请回答"%s"或"%s".
 过程语言 用户 "%s" 将被永久删除.
 新的角色是否是超级用户? 新的角色允许创建数据库吗? 新角色允许创建其它新的角色吗?  是否信任? 请用 "%s --help" 获取更多的信息.
 使用方法:
 n no 内存溢出
 pg_strdup: 无法复制空指针 (内部错误)
 y yes 