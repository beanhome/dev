��    v      �  �   |      �	      �	     
  &   $
     K
     k
  -   �
     �
     �
  =   �
       �   <     �  a   �  K   K     �  A   �  !   �  3     ?   J  ?   �  H   �  D     C   X  E   �  ?   �  >   "  9   a  B   �  <   �  �     0   �  F   �  >     8   W  I   �  %   �  2      O   3  7   �     �     �     �  �   �  -   n  !   �  C   �  y     C   |  D   �  >     A   D  *   �  /   �  %   �  /     #   7     [  3   y  0   �  ,   �  .     3   :  -   n  0   �  5   �  :     *   >  "   i  $   �  J   �     �       3   /  0   c     �     �  !   �  $   �        -   .  4   \  %   �  $   �  "   �  !   �  F   !  F   h     �  7   �  )   �  k   %  `   �  %   �  &        ?  d   G     �  &   �  0   �  .   #  )   R  )   |  "   �      �  (   �       !   .     P     d     �     �     �     �     �     �  "   �        �  3   V   "  -   i"  U   �"  :   �"  E   (#  g   n#  "   �#     �#  Z   $  &   o$  �   �$  9   x%  �   �%  {   K&  4   �&  u   �&  )   r'  R   �'  E   �'  x   5(  g   �(  k   )  x   �)  �   �)  O   |*  a   �*  Q   .+  �   �+  \   ,  �   {,  C   J-  �   �-  w   .  O   �.  �   �.  G   c/  b   �/  �   0  h   �0     51     D1  %   S1  E  y1  Y   �2  0   3  �   J3  R  �3  �   &5  �   �5  �   \6  �   7  L   �7  O   �7  =   28  Q   p8  D   �8  9   9  c   A9  `   �9  J   :  Z   Q:  �   �:  U   /;  U   �;  S   �;  u   /<  ?   �<  9   �<  G   =  �   g=  '   �=  1   >  c   Q>  V   �>  %   ?  5   2?  3   h?  >   �?  <   �?  \   @  h   u@  >   �@  >   A  <   \A  <   �A  �   �A  �   mB  "   �B  �   C  I   �C  �   �C  �   �D  M   4E  X   �E     �E  �   �E  2   �F  V   �F  h   8G  L   �G  K   �G  D   :H  C   H  2   �H  P   �H  8   GI  :   �I  &   �I  2   �I  -   J  /   CJ     sJ  $   �J  "   �J  G   �J  D    K  1   eK     g      v       4   l   u       [   R   _   O   s           :       S       i      C      0   	   L   q   U       8   M   J       .   1              &      \      #      -   X   3          ,         ]            =                 F       d   
   W      A   m   Q       7   r   G   K           ^   b   %                      5   $   D   `   '       E      N          t   ?       H          P       V   "          9   !   <       h   *   e   I           2      (   k       )   o       +       Z             6   @   T   f       Y   p   n              /          B      >   j          ;   c       a    
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
 
Start types are:
   %s init[db]               [-D DATADIR] [-s] [-o "OPTIONS"]
   %s kill    SIGNALNAME PID
   %s register   [-N SERVICENAME] [-U USERNAME] [-P PASSWORD] [-D DATADIR]
                    [-S START-TYPE] [-w] [-t SECS] [-o "OPTIONS"]
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
   -S START-TYPE   service start type to register PostgreSQL server
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
   auto       start service automatically during system startup (default)
   demand     start service on demand
   fast        quit directly, with proper shutdown
   immediate   quit without complete shutdown; will lead to recovery on restart
   smart       quit after all clients have disconnected
  done
  failed
  stopped waiting
 %s is a utility to start, stop, restart, reload configuration files,
report the status of a PostgreSQL server, or signal a PostgreSQL process.

 %s: -S option not supported on this platform
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
 %s: could not wait for server because of misconfiguration
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
 %s: unrecognized start type "%s"
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
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not read binary "%s" could not read symbolic link "%s" invalid binary "%s" server is still starting up
 server shutting down
 server signaled
 server started
 server starting
 server stopped
 starting server anyway
 waiting for server to shut down... waiting for server to start... Project-Id-Version: PostgreSQL 9.1
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-11-29 18:40+0000
PO-Revision-Date: 2010-12-01 01:17+0700
Last-Translator: Andrey Sudnik <sudnikand@gmail.com>
Language-Team: pgsql-ru-general <pgsql-ru-general@postgresql.org>
Language: 
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Russian
X-Poedit-Country: RUSSIAN FEDERATION
X-Poedit-SourceCharset: utf-8
 
Разрешённые названия сигналов для команды kill:
 
Опции общего характера:
 
Опции для регистрации и снятия с регистрации:
 
Опции запуска или перезапуска:
 
Опции для остановки или перезапуска:
 
Посылать сообщения об ошибках на адрес  <pgsql-bugs@postgresql.org>.
 
Режимы остановки:
 
Типы запуска:
   %s init[db]               [-D ДИРЕКТОРИЯ-ДАННЫХ] [-s] [-o "ОПЦИИ"]
   %s kill   ИМЯ-СИГНАЛА PID
   %s register   [-N ИМЯ-СЛУЖБЫ] [-U ИМЯ-ПОЛЬЗОВАТЕЛЯ] [-P ПАРОЛЬ] [-D ДИРЕКТОРИЯ-ДАННЫХ]
                    [-S ТИП-ЗАПУСКА] [-w] [-t СЕКУНДЫ] [-o "ОПЦИИ"]
   %s reload  [-D ДИРЕКТОРИЯ-ДАННЫХ] [-s]
   %s restart [-w] [-t СЕКУНДЫ] [-D ДИРЕКТОРИЯ-ДАННЫХ] [-s] [-m РЕЖИМ-ОСТАНОВКИ]
                 [-o "ОПЦИИ"]
   %s start   [-w] [-t СЕКУНДЫ] [-D ДИРЕКТОРИЯ-ДАННЫХ] [-s] [-l ИМЯ-ФАЙЛА] [-o "ОПЦИИ"]
   %s status  [-D ДИРЕКТОРИЯ-ДАННЫХ]
   %s stop    [-W] [-t СЕКУНДЫ] [-D ДИРЕКТОРИЯ-ДАННЫХ] [-s] [-m РЕЖИМ-ОСТАНОВКИ]
   %s unregister [-N ИМЯ-СЛУЖБЫ]
   --help                 показать эту подсказку и выйти
   --version              показать версию и выйти
   -D, --pgdata ДИРЕКТОРИЯ-ДАННЫХ  местонахождение хранилища баз данных
   -N ИМЯ-СЛУЖБЫ   имя службы для регистрации сервера PostgreSQL
   -P ПАРОЛЬ    пароль аккаунта для регистрации сервера PostgreSQL
   -S ТИП-ЗАПУСКА   тип запуска службы для регистрации сервера PostgreSQL
   -U ИМЯ-ПОЛЬЗОВАТЕЛЯ    имя пользователя для регистрации сервера PostgreSQL
   -W                     не ждать завершения операции
   -c, --core-files       разрешить postgres'у генерировать core-файлы
   -c, --core-files       неприменимо на этой платформе
   -l, --log ИМЯ-ФАЙЛА    записывать (или добавлять) протокол выполнения сервера в ИМЯ-ФАЙЛА.
   -m РЕЖИМ-ОСТАНОВКИ   может быть "smart", "fast" или "immediate"
   -o OPTIONS             опции командной строки для передачи postgres
                         (исполнительный файл сервера PostgreSQL) или initdb
   -p ПУТЬ-К-POSTGRES     обычно не требуется
   -s, --silent           сообщать только ошибки, исключая информационные сообщения
   -t СЕКУНДЫ             сколько секунд ждать при использовании опции -w
   -w                     ждать до завершения операции
   auto       запускать сервис автоматически при старте системы (по умолчанию)
   demand     запускать сервис по требованию
   fast        закончить быстро,но с полноценной остановкой
   immediate   выйти немедленно без полноценной остановки; приведёт к
              восстановлению при перезапуске
   smart       закончить работу после отключения всех клиентов
  готово
  ошибка
  остановка ожидания
 %s является утилитой для запуска, остановки, перезапуска,
перезагрузки конфигурационных файлов, информирования о состоянии сервера
PostgreSQL, или отправки сигналов PostgreSQL-процессу.

 %s: опция -S не поддерживается на данной платформе
 %s: PID-файл "%s" не существует
 %s: возможно, другой сервер уже запущен, пробуем запустить сервер всё равно
 %s: нельзя выполнять под пользователем root
Пожалуйста, войдите в систему как непривилегированный пользователь  (например, используя "su"),
под которым будет выполняться серверный процесс.
 %s: невозможно перезагрузить сервер; выполняется однопользовательский сервер (PID: %ld)
 %s: невозможно перезапустить сервер; выполняется однопользовательский сервер (PID: %ld)
 %s: не удалось установить ограничение на размер core-файла; отвергнуто жёстким ограничением
 %s: не удалось остановить сервер; выполняется однопользовательский сервер (PID: %ld)
 %s: не удалось найти свой исполняемый файл
 %s: не удалось найти исполняемый файл postgres'а
 %s: не удалось открыть PID-файл "%s": %s
 %s: не удалось открыть службу "%s": код ошибки %d
 %s: невозможно открыть менеджер служб
 %s: не удалось прочитать файл "%s"
 %s: не удалось зарегистрировать службу "%s": код ошибки %d
 %s: не удалось отправить сигнал перезагрузки (PID: %ld): %s
 %s: не удалось отправить сигнал %d (PID: %ld): %s
 %s: не удалось отправить сигнал остановки (PID: %ld): %s
 %s: не удалось запустить сервер
Проверьте вывод в протоколе выполнения.
 %s: не удалось запустить сервер, код возврата: %d
 %s: не удалось запустить службу "%s": код ошибки %d
 %s: невозможно удалить службу "%s": код ошибки %d

 %s: не удалось дождаться сервера вследствие ошибки конфигурации
 %s: создание базы данных не удалось
 %s: неверные данные в PID-файле "%s"
 %s: отсутствуют аргументы для режима kill
 %s: директория баз данных не указана и переменная окружения PGDATA не установлена
 %s: команда не указана
 %s: нет запущенного сервера
 %s: похоже что старый процесс сервера (PID: %ld) завершился
 %s: файл опций "%s" должен иметь ровно одну строку
 %s: не хватает памяти
 %s: сервер не останавливается
 %s: выполняется сервер (PID: %ld)
 %s: служба "%s" уже зарегистрирована
 %s: служба "%s" не зарегистрирована
 %s: выполняется однопользовательский сервер (PID: %ld)
 %s: слишком много аргументов командной строки (первый: "%s")
 %s: нераспознанный режим работы "%s"
 %s: неизвестный режим остановки "%s"
 %s: нераспознанное имя сигнала "%s"
 %s: нераспознанный тип запуска "%s"
 (По умолчанию, ждать завершения остановки, но не в случае запуска или перезапуска

 Если опция -D не задана,то будет использоваться переменная окружения PGDATA.
 Запущен ли сервер?
 Пожалуйста, остановите однопользовательский сервер и попытайтесь снова.
 Сервер запущен и принимает подключения
 Программа "%s" нужна для %s, но не найдена
в той же директории, что и "%s".
Проверьте вашу установку.
 Программа "%s" найдена рядом с "%s",
но не той же версии, что и %s.
Проверьте вашу установку.
 Превышено время ожидания запуска сервера
 Наберите "%s --help" для более подробной информации.
 Использование:
 ВНИМАНИЕ: активен режим онлайн резервирования
Выключение не завершится пока не вызовут pg_stop_backup().

 Ожидание запуска сервера...
 дочерний процесс завершился с кодом возврата %d дочерний процесс завершился с нераспознанным статусом %d дочерний процесс завершён исключением 0x%X дочерний процесс был завершен сигналом %d дочерний процесс завершён сигналом %s не удалось поменять директорию на "%s" "%s" не найден для выполнения не удалось определить текущую директорию: %s не удалось считать бинарный "%s" не получилось считать ссылку "%s" неверный бинарный "%s" сервер всё ещё запускается
 сервер завершает работу
 отправлен сигнал серверу
 сервер запущен
 сервер запускается
 сервер остановлен
 сервер запускается, несмотря ни на что
 ожидание завершения работы сервера... ожидание запуска сервера... 