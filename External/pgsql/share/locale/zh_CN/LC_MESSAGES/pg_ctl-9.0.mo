��    m      �  �   �      @	      A	     b	  &   t	     �	     �	  -   �	     
  =   
     \
  |   y
     �
  a     K   x     �  A   �  !   !  3   C  ?   w  ?   �  H   �  D   @  E   �  ?   �  >     9   J  B   �  <   �  �     0   �  F   �  >     8   @  2   y  O   �  7   �     4     ;  �   D  !   �  C   �  y   ;  C   �  D   �  >   >  A   }  *   �  /   �  %     /   @  #   p     �  3   �  0   �  ,     .   D  3   s  -   �  0   �  5     *   <  "   g  $   �  J   �     �       3   -  0   a     �     �  !   �  $   �        -   ,  4   Z  %   �  $   �  "   �  F   �  F   D     �  7   �  )   �  k     `   m  %   �  &   �       d   #     �  &   �  0   �  .   �  )   .  )   X  "   �      �  (   �     �  !   
     ,     @     V     g     w     �     �  "   �     �  Z  �     M     l     |     �     �  .   �     �  A      $   `   |   �   $   !  e   '!  S   �!     �!  G   "  "   I"  =   l"  :   �"  3   �"  D   #  B   ^#  F   �#  2   �#  @   $  5   \$  N   �$  C   �$     %%  /   �%  C   �%  D   &  2   ^&  ,   �&  8   �&  3   �&     +'     4'  �   ='     �'  I   �'  m   +(  a   �(  W   �(  B   S)  W   �)     �)  .   *  %   ;*  *   a*      �*     �*  *   �*  ,   �*  )   "+  ,   L+  4   y+  1   �+  *   �+  *   ,  #   6,  )   Z,     �,  E   �,     �,  %    -  6   &-  &   ]-     �-     �-  *   �-      �-      .  :   .  .   Y.     �.     �.     �.  4   �.  :   /  #   U/  ;   y/  +   �/  \   �/  R   >0  "   �0  *   �0     �0  l   �0      [1  #   |1  #   �1  )   �1     �1     2     (2  !   @2     b2     2     �2     �2     �2     �2     3     -3     J3     g3     �3     �3               6      7         =          [           )      :   /   $          f           (   a   T   Y   M   >   _   g      D   F   '       R   J          .   &              k      8       U   ;                N   I   C   b   5      E               +       \   L   	   V          e          
   H   B       "   #   !   -   ?      4       l               W   i      X               ]   ^          2   %      A   3       0       `   Q          P   m   9   ,   @           d   j                               S   O   h   G   Z           c   1       *   K   <           
Allowed signal names for kill:
 
Common options:
 
Options for register and unregister:
 
Options for start or restart:
 
Options for stop or restart:
 
Report bugs to <pgsql-bugs@postgresql.org>.
 
Shutdown modes are:
   %s init[db]               [-D DATADIR] [-s] [-o "OPTIONS"]
   %s kill    SIGNALNAME PID
   %s register   [-N SERVICENAME] [-U USERNAME] [-P PASSWORD] [-D DATADIR]
                    [-w] [-t SECS] [-o "OPTIONS"]
   %s reload  [-D DATADIR] [-s]
   %s restart [-w] [-t SECS] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
                 [-o "OPTIONS"]
   %s start   [-w] [-t SECS] [-D DATADIR] [-s] [-l FILENAME] [-o "OPTIONS"]
   %s status  [-D DATADIR]
   %s stop    [-W] [-t SECS] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
   %s unregister [-N SERVICENAME]
   --help                 show this help, then exit
   --version              output version information, then exit
   -D, --pgdata DATADIR   location of the database storage area
   -N SERVICENAME  service name with which to register PostgreSQL server
   -P PASSWORD     password of account to register PostgreSQL server
   -U USERNAME     user name of account to register PostgreSQL server
   -W                     do not wait until operation completes
   -c, --core-files       allow postgres to produce core files
   -c, --core-files       not applicable on this platform
   -l, --log FILENAME     write (or append) server log to FILENAME
   -m SHUTDOWN-MODE   can be "smart", "fast", or "immediate"
   -o OPTIONS             command line options to pass to postgres
                         (PostgreSQL server executable) or initdb
   -p PATH-TO-POSTGRES    normally not necessary
   -s, --silent           only print errors, no informational messages
   -t SECS                seconds to wait when using -w option
   -w                     wait until operation completes
   fast        quit directly, with proper shutdown
   immediate   quit without complete shutdown; will lead to recovery on restart
   smart       quit after all clients have disconnected
  done
  failed
 %s is a utility to start, stop, restart, reload configuration files,
report the status of a PostgreSQL server, or signal a PostgreSQL process.

 %s: PID file "%s" does not exist
 %s: another server might be running; trying to start server anyway
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: cannot reload server; single-user server is running (PID: %ld)
 %s: cannot restart server; single-user server is running (PID: %ld)
 %s: cannot set core file size limit; disallowed by hard limit
 %s: cannot stop server; single-user server is running (PID: %ld)
 %s: could not find own program executable
 %s: could not find postgres program executable
 %s: could not open PID file "%s": %s
 %s: could not open service "%s": error code %d
 %s: could not open service manager
 %s: could not read file "%s"
 %s: could not register service "%s": error code %d
 %s: could not send reload signal (PID: %ld): %s
 %s: could not send signal %d (PID: %ld): %s
 %s: could not send stop signal (PID: %ld): %s
 %s: could not start server
Examine the log output.
 %s: could not start server: exit code was %d
 %s: could not start service "%s": error code %d
 %s: could not unregister service "%s": error code %d
 %s: database system initialization failed
 %s: invalid data in PID file "%s"
 %s: missing arguments for kill mode
 %s: no database directory specified and environment variable PGDATA unset
 %s: no operation specified
 %s: no server running
 %s: old server process (PID: %ld) seems to be gone
 %s: option file "%s" must have exactly one line
 %s: out of memory
 %s: server does not shut down
 %s: server is running (PID: %ld)
 %s: service "%s" already registered
 %s: service "%s" not registered
 %s: single-user server is running (PID: %ld)
 %s: too many command-line arguments (first is "%s")
 %s: unrecognized operation mode "%s"
 %s: unrecognized shutdown mode "%s"
 %s: unrecognized signal name "%s"
 (The default is to wait for shutdown, but not for start or restart.)

 If the -D option is omitted, the environment variable PGDATA is used.
 Is server running?
 Please terminate the single-user server and try again.
 Server started and accepting connections
 The program "%s" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "%s" was found by "%s"
but was not the same version as %s.
Check your installation.
 Timed out waiting for server startup
 Try "%s --help" for more information.
 Usage:
 WARNING: online backup mode is active
Shutdown will not complete until pg_stop_backup() is called.

 Waiting for server startup...
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not read binary "%s" could not read symbolic link "%s" invalid binary "%s" server shutting down
 server signaled
 server started
 server starting
 server stopped
 starting server anyway
 waiting for server to shut down... waiting for server to start... Project-Id-Version: pg_ctl (PostgreSQL 9.0)
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-10-01 14:41+0000
PO-Revision-Date: 2010-10-01 12:49+0800
Last-Translator: Weibin <ssmei_2000@yahoo.com>
Language-Team: Chinese (Simplified)
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 
允许关闭的信号名称:
 
普通选项:
 
注册或注销的选项:
 
启动或重启的选项:
 
停止或重启的选项:
 
臭虫报告至 <pgsql-bugs@postgresql.org>.
 
关闭模式有如下几种:
   %s init[db]               [-D 数据目录] [-s] [-o "选项"]
   %s kill    信号名称 进程号
   %s register   [-N 服务名称] [-U 用户名] [-P 口令] [-D 数据目录]
              [-w] [-t 秒数] [-o "选项"]
   %s reload  [-D 数据目录] [-s]
   %s restart [-w] [-t 秒数] [-D 数据目录] [-s] [-m 关闭模式]
                [-o "选项"]
   %s start   [-w]  [-t 秒数] [-D 数据目录] [-s] [-l 文件名] [-o "选项"]
   %s status  [-D 数据目录]
   %s stop   [-w]  [-t 秒数] [-D 数据目录] [-s] [-m 关闭模式]
   %s unregister [-N 服务名称]
   --help                 显示此帮助信息, 然后退出
   --version              显示版本信息, 然后退出
   -D, --pgdata 数据目录  数据存储的位置
   -N 服务名称     注册到 PostgreSQL 服务器的服务名称
   -P 口令         注册到 PostgreSQL 服务器帐户的口令
   -U 用户名       注册到 PostgreSQL 服务器帐户的用户名
   -W                     不用等待操作完成
   -c, --core-files       允许postgres进程产生核心文件
   -c, --core-files       在这种平台上不可用
   -l, --log FILENAME     写入 (或追加) 服务器日志到文件 FILENAME
   -m SHUTDOWN-MODE   可以是 "smart", "fast", 或者 "immediate"
   -o OPTIONS             传递给postgres的命令行选项
                      (PostgreSQL 服务器执行文件)或initdb
   -p PATH-TO-POSTMASTER  正常情况不必要
   -s, --silent           只打印错误信息, 没有其他信息
   -t SECS                当使用-w 选项时需要等待的秒数
   -w                     等待直到操作完成
   fast        直接退出, 正确的关闭
   immediate   不完全的关闭退出; 重启后恢复
   smart       所有客户端断开连接后退出
  完成
  失败
 %s 是一个启动, 停止, 重启, 重载配置文件, 报告 PostgreSQL 服务器状态,
或者杀掉 PostgreSQL 进程的工具

 %s: PID 文件 "%s" 不存在
 %s: 其他服务器进程可能正在运行; 尝试启动服务器进程
 %s: 无法以 root 用户运行
请以服务器进程所属用户 (非特权用户) 登录 (或使用 "su")

 %s: 无法重新加载服务器进程；正在运行单用户模式的服务器进程 (PID: %ld)
 %s: 无法重启服务器进程; 单用户模式服务器进程正在运行 (PID: %ld)
 %s: 不能设置核心文件大小的限制;磁盘限额不允许
 %s: 无法停止服务器进程; 正在运行 单用户模式服务器进程(PID: %ld)
 %s: 无法找到执行文件
 %s: 无法找到postgres程序的执行文件
 %s: 无法打开 PID 文件 "%s": %s
 %s: 无法打开服务 "%s": 错误码 %d
 %s: 无法打开服务管理器
 %s: 无法读取文件 "%s"
 %s: 无法注册服务 "%s": 错误码 %d
 %s: 无法发送重载信号 (PID: %ld): %s
 %s: 无法发送信号 %d (PID: %ld): %s
 %s: 无法发送停止信号 (PID: %ld): %s
 %s: 无法启动服务器进程
检查日志输出.
 %s: 无法启动服务器进程: 退出码为 %d
 %s: 无法启动服务 "%s": 错误码 %d
 %s: 无法注销服务 "%s": 错误码 %d
 %s: 数据库系统初始化失败
 %s: PID文件 "%s" 中存在无效数据
 %s: 缺少 kill 模式参数
 %s: 没有指定数据目录, 并且没有设置 PGDATA 环境变量
 %s: 没有指定操作
 %s:没有服务器进程正在运行
 %s: 原有的进程(PID: %ld)可能已经不存在了
 %s: 选项文件 "%s" 只能有一行
 %s: 内存溢出
 %s: server进程没有关闭
 %s: 正在运行服务器进程(PID: %ld)
 %s: 服务 "%s" 已经注册了
 %s: 服务 "%s" 没有注册
 %s: 正在运行单用户模式服务器进程 (PID: %ld)
 %s: 命令行参数太多 (第一个是 "%s")
 %s: 无效的操作模式 "%s"
 %s: 无效的关闭模式 "%s"
 %s: 无效信号名称 "%s"
 (默认为关闭等待, 但不是启动或重启.)

 如果省略了 -D 选项, 将使用 PGDATA 环境变量.
 服务器进程是否正在运行?
 请终止单用户模式服务器进程，然后再重试.
 服务器进程已启动并且接受连接
 %2$s需要程序"%1$s", 但是在同一个目录"%3$s"中没找到.

请检查您的安装.
 "%2$s"找到程序 "%1$s", 但是和版本 "%3$s" 不一致.

检查您的安装.
 在等待服务器启动时超时
 试用 "%s --help" 获取更多的信息.
 使用方法:
 警告: 在线备份模式处于激活状态
关闭命令将不会完成，直到调用了pg_stop_backup().
 等待服务器进程启动 ...
 子进程已退出, 退出码为 %d 子进程已退出, 未知状态 %d 子进程被例外(exception) 0x%X 终止 子进程被信号 %d 终止 子进程被信号 %s 终止 无法进入目录 "%s" 未能找到一个 "%s" 来执行 无法确认当前目录: %s 无法读取二进制码 "%s" 无法读取符号链结 "%s" 无效的二进制码 "%s" 正在关闭服务器进程
 服务器进程发出信号
 服务器进程已经启动
 正在启动服务器进程
 服务器进程已经关闭
 正在启动服务器进程
 等待服务器进程关闭 ... 等待服务器进程启动 ... 