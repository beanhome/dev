��    �      4  �   L        R        l  
   �     �  -   �  �   �  �   ^    �  A     5   H  J   ~     �  6   �  P     C   m  :   �  ]   �  4   J  B     H   �  G     >   S  9   �  3   �  ?      /   @  -   p  y   �  (     #   A  7   e  (   �  ,   �  '   �  3     D   O  (   �  8   �  -   �  -   $  /   R  "   �  6   �  +   �       0     ;   P  $   �  /   �     �  $   �  ~   $  1   �     �  /   �  J   #  �   n     6  C   I  -   �  8   �  !   �  ,     /   C  4   s  A   �  @   �  ,   +  P   X  I   �  b   �     V     g  �   �  [   
     f          �  ;   �  9   �  �   +  >   �  ;   �    7  u   H   q   �   f   0!  s   �!  &   "     2"     :"  &   I"  0   p"  .   �"  )   �"  )   �"  "   $#  #   G#  "   k#      �#  (   �#  "   �#     �#  "   $  !   9$  ,   [$  $   �$  *   �$  %   �$  !   �$      %     :%     U%      p%     �%     �%  -   �%  0   �%     (&     G&     c&  *   w&  )   �&     �&     �&  &   �&  %   '     ,'  +   B'  !   n'  �  �'  �   u)  1   *     C*     Q*  F   l*  �   �*  5  k+  g  �,  o   	.  @   y.  w   �.  9   2/  O   l/  �   �/  ~   O0  R   �0  �   !1  Y   �1  H   )2  m   r2  {   �2  `   \3  H   �3  U   4  {   \4  <   �4  P   5  +  f5  ;   �6  1   �6  W    7  E   X7  X   �7  C   �7  b   ;8  �   �8  ^   39  m   �9  M    :  M   N:  M   �:  >   �:  l   );  H   �;  4   �;  b   <  y   w<  K   �<  b   ==  ,   �=  D   �=  �   >  u   �>  0   X?  [   �?  �   �?  a  r@  %   �A  r   �A  S   mB  j   �B  <   ,C  S   iC  h   �C  h   &D  �   �D  �   E  N   �E  �   �E  �   �F  �   EG  "   �G  E   H    YH  �   _I  &   'J  2   NJ  5   �J  �   �J  c   WK  �   �K  R   �L  }   �L  !  `M    �O  �   �P  �   NQ  �   �Q  X   �R     S  "    S  V   CS  h   �S  L   T  D   PT  D   �T  1   �T  2   U  C   ?U  2   �U  \   �U  A   V  8   UV  E   �V  O   �V  Q   $W  >   vW  b   �W  L   X  C   eX  (   �X  &   �X  -   �X  =   'Y  0   eY  C   �Y  5   �Y  Z   Z  8   kZ  )   �Z  &   �Z  N   �Z  J   D[     �[     �[  Y   �[  X   \  $   g\  Y   �\  4   �\           V       k   A   S   c              o   O   !       \   9   i       C   >   y   (       g          ]           t          z   b      <   ?   s          )   m      r      f       H   �       Y   W   l   [   /   _   N   U       `   B       h                                L           "   @   F   a   0   #   1   :          P   Q   '   ;   j   ,             8              4      �   	   K              -       �   e      M              d               %       I   n      �      +   ^   3   =   D   6              7   w   J   u   Z       $       .       q      ~       x   p       X          
   E         T       G       }          {   &   2       R          *   |   v   5        
If the data directory is not specified, the environment variable PGDATA
is used.
 
Less commonly used options:
 
Options:
 
Other options:
 
Report bugs to <pgsql-bugs@postgresql.org>.
 
Success. You can now start the database server using:

    %s%s%spostgres%s -D %s%s%s
or
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
WARNING: enabling "trust" authentication for local connections
You can change this by editing pg_hba.conf or using the -A option the
next time you run initdb.
       --lc-collate=, --lc-ctype=, --lc-messages=LOCALE
      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE
                            set default locale in the respective category for
                            new databases (default taken from environment)
       --locale=LOCALE       set default locale for new databases
       --no-locale           equivalent to --locale=C
       --pwfile=FILE         read password for the new superuser from file
   %s [OPTION]... [DATADIR]
   -?, --help                show this help, then exit
   -A, --auth=METHOD         default authentication method for local connections
   -E, --encoding=ENCODING   set default encoding for new databases
   -L DIRECTORY              where to find the input files
   -T, --text-search-config=CFG
                            default text search configuration
   -U, --username=NAME       database superuser name
   -V, --version             output version information, then exit
   -W, --pwprompt            prompt for a password for the new superuser
   -X, --xlogdir=XLOGDIR     location for the transaction log directory
   -d, --debug               generate lots of debugging output
   -n, --noclean             do not clean up after errors
   -s, --show                show internal settings
  [-D, --pgdata=]DATADIR     location for this database cluster
 %s initializes a PostgreSQL database cluster.

 %s: "%s" is not a valid server encoding name
 %s: cannot be run as root
Please log in (using, e.g., "su") as the (unprivileged) user that will
own the server process.
 %s: could not access directory "%s": %s
 %s: could not access file "%s": %s
 %s: could not change permissions of directory "%s": %s
 %s: could not create directory "%s": %s
 %s: could not create symbolic link "%s": %s
 %s: could not execute command "%s": %s
 %s: could not find suitable encoding for locale %s
 %s: could not find suitable text search configuration for locale %s
 %s: could not get current user name: %s
 %s: could not obtain information about current user: %s
 %s: could not open file "%s" for reading: %s
 %s: could not open file "%s" for writing: %s
 %s: could not read password from file "%s": %s
 %s: could not write file "%s": %s
 %s: data directory "%s" not removed at user's request
 %s: directory "%s" exists but is not empty
 %s: encoding mismatch
 %s: failed to remove contents of data directory
 %s: failed to remove contents of transaction log directory
 %s: failed to remove data directory
 %s: failed to remove transaction log directory
 %s: file "%s" does not exist
 %s: file "%s" is not a regular file
 %s: input file "%s" does not belong to PostgreSQL %s
Check your installation or specify the correct path using the option -L.
 %s: input file location must be an absolute path
 %s: invalid locale name "%s"
 %s: locale %s requires unsupported encoding %s
 %s: must specify a password for the superuser to enable %s authentication
 %s: no data directory specified
You must identify the directory where the data for this database system
will reside.  Do this with either the invocation option -D or the
environment variable PGDATA.
 %s: out of memory
 %s: password prompt and password file cannot be specified together
 %s: removing contents of data directory "%s"
 %s: removing contents of transaction log directory "%s"
 %s: removing data directory "%s"
 %s: removing transaction log directory "%s"
 %s: symlinks are not supported on this platform %s: too many command-line arguments (first is "%s")
 %s: transaction log directory "%s" not removed at user's request
 %s: transaction log directory location must be an absolute path
 %s: unrecognized authentication method "%s"
 %s: warning: specified text search configuration "%s" might not match locale %s
 %s: warning: suitable text search configuration for locale %s is unknown
 Encoding %s is not allowed as a server-side encoding.
Rerun %s with a different locale selection.
 Enter it again:  Enter new superuser password:  If you want to create a new database system, either remove or empty
the directory "%s" or run %s
with an argument other than "%s".
 If you want to store the transaction log there, either
remove or empty the directory "%s".
 Passwords didn't match.
 Rerun %s with the -E option.
 Running in debug mode.
 Running in noclean mode.  Mistakes will not be cleaned up.
 The database cluster will be initialized with locale %s.
 The database cluster will be initialized with locales
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 The default database encoding has accordingly been set to %s.
 The default text search configuration will be set to "%s".
 The encoding you selected (%s) and the encoding that the
selected locale uses (%s) do not match.  This would lead to
misbehavior in various character string processing functions.
Rerun %s and either do not specify an encoding explicitly,
or choose a matching combination.
 The files belonging to this database system will be owned by user "%s".
This user must also own the server process.

 The program "postgres" is needed by %s but was not found in the
same directory as "%s".
Check your installation.
 The program "postgres" was found by "%s"
but was not the same version as %s.
Check your installation.
 This might mean you have a corrupted installation or identified
the wrong directory with the invocation option -L.
 Try "%s --help" for more information.
 Usage:
 caught signal
 child process exited with exit code %d child process exited with unrecognized status %d child process was terminated by exception 0x%X child process was terminated by signal %d child process was terminated by signal %s copying template1 to postgres ...  copying template1 to template0 ...  could not change directory to "%s" could not find a "%s" to execute could not identify current directory: %s could not open directory "%s": %s
 could not read binary "%s" could not read directory "%s": %s
 could not read symbolic link "%s" could not remove file or directory "%s": %s
 could not set junction for "%s": %s
 could not stat file or directory "%s": %s
 could not write to child process: %s
 creating configuration files ...  creating conversions ...  creating dictionaries ...  creating directory %s ...  creating information schema ...  creating subdirectories ...  creating system views ...  creating template1 database in %s/base/1 ...  fixing permissions on existing directory %s ...  initializing dependencies ...  initializing pg_authid ...  invalid binary "%s" loading PL/pgSQL server-side language ...  loading system objects' descriptions ...  ok
 out of memory
 selecting default max_connections ...  selecting default shared_buffers ...  setting password ...  setting privileges on built-in objects ...  vacuuming database template1 ...  Project-Id-Version: PostgreSQL 9 current
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-11-29 18:40+0000
PO-Revision-Date: 2010-11-30 16:12+0600
Last-Translator: Andrey Sudnik <sudnikand@yandex.ru>
Language-Team: pgsql-ru-general <pgsql-ru-general@postgresql.org>
Language: 
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Russian
X-Poedit-Country: RUSSIAN FEDERATION
X-Poedit-SourceCharset: utf-8
 
Если директория данных не указана, используется значение переменной окружения PGDATA.
 
Редко используемые опции:
 
Опции:
 
Другие опции:
 
Сообщения об ошибках: <pgsql-bugs@postgresql.org>.
 
Успех. Вы теперь можете запустить сервер баз данных:

    %s%s%spostgres%s -D %s%s%s
или
    %s%s%spg_ctl%s -D %s%s%s -l logfile start

 
ВНИМАНИЕ: используется аутентификация "trust" для локальных подключений.
Вы можете её поменять, отредактировав pg_hba.conf или используя опцию -A,
при следующем выполнении initdb.
       --lc-collate=, --lc-ctype=, --lc-messages=LOCALE
      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE
                            установить локаль в соответствующей категории для
                            новых баз (значения по умолчанию берутся из окружения)
       --locale=LOCALE       установить локаль по умолчанию для новых баз
       --no-locale           эквивалентно --locale=C
       --pwfile=FILE         читать пароль для нового администратора из файла
   %s [ОПЦИИ]... [ДИРЕКТОРИЯ-ДАННЫХ]
   -?, --help                показать эту помощь и выйти
   -A, --auth=МЕТОД          метод аутентификации по умолчанию для локальных подключений
   -E, --encoding=КОДИРОВКА  установить кодировку по умолчанию для новых баз
   -L ДИРЕКТОРИЯ             где найти входные файлы
   -T, --text-search-config=КОНФИГУРАЦИЯ
                            конфигурация полнотекстового поиска по умолчанию
   -U, --username=ИМЯ        имя администратора базы данных
   -V, --version             показать версию и выйти
   -W, --pwprompt            запросить пароль для нового администратора
   -X, --xlogdir=XLOGDIR     местонахождение для директории журнала транзакций
   -d, --debug               выдавать много отладочных сообщений
   -n, --noclean             не очищать после ошибок
   -s, --show                показать внутренние установки
  [-D, --pgdata=]ДИР-ДАННЫХ  местонахождение для этого кластера баз данных
 %s инициализирует кластер PostgreSQL.

 %s: "%s" не является верной кодировкой сервера
 %s: нельзя запускать под root'ом
Пожалуйста, зайдите как (непривилегированный) пользователь (например,
используя "su"), под которым будет выполняться серверный процесс.
 %s: нет доступа к директории "%s": %s
 %s: нет доступа к файлу "%s": %s
 %s: не удалось поменять права на директорию "%s": %s
 %s: не удалось создать директорию "%s": %s
 %s: не удалось создать символическую ссылку "%s": %s
 %s: не удалось выполнить команду "%s": %s
 %s: не удалось найти подходящую кодировку для локали %s
 %s: не удалось найти подходящую конфигурацию полнотекстового поиска для локали %s
 %s: не удалось получить имя текущего пользователя: %s
 %s: не удалось получить информацию о текущем пользователе: %s
 %s: не удалось открыть файл "%s" для чтения: %s
 %s: не удалось открыть файл "%s" для записи: %s
 %s: не удалось считать пароль из файла "%s": %s
 %s: не удалось записать в файл "%s": %s
 %s: директория данных "%s" не удалена по запросу пользователя
 %s: директория "%s" существует но не пуста
 %s: несоответствие кодировки
 %s: ошибка при удалении содержимого директории данных
 %s: ошибка при удалении содержимого директории журнала транзакций
 %s: ошибка при удалении директории данных
 %s: ошибка при удалении директории журнала транзакций
 %s: файл "%s" не существует
 %s: файл "%s" не является обычным файлом
 %s: входной файл "%s" не принадлежит PostgreSQL %s
Проверьте вашу установку или укажите правильный путь с помощью опции -L.
 %s: местонахождение входного файла должно быть абсолютным путём
 %s: ошибочное имя локали "%s"
 %s: локаль %s требует не поддерживаемую кодировку %s
 %s: необходимо указать пароль администратора для включения аутентификации %s
 %s: директория данных не указана
Вы должны указать директорию для расположения данных для
для этой системы.  Это можно сделать с помощью указания опции -D
или установки переменной окружения PGDATA.
 %s: не хватило памяти
 %s: нельзя указывать одновременно запрос пароля и файл паролей
 %s: удаление содержимого директории данных "%s"
 %s: удаление содержимого директории журнала транзакций "%s"
 %s: удаление директории данных "%s"
 %s: удаление директории журнала транзакций "%s"
 %s: символьные ссылки не поддерживаются на этой платформе %s: слишком много аргументов командной строки (первый: "%s")
 %s: директория журнала транзакций "%s" не удалена по запросу пользователя
 %s: местонахождение директории журнала транзакций должно быть абсолютным путём
 %s: нераспознанный метод аутентификации "%s"
 %s: внимание: указанная конфигурация полнотекстового поиска "%s" может не соответствовать локали %s
 %s: внимание: подходящая конфигурация полнотекстового поиска для локали %s неизвестна
 Кодировка %s недопустима в качестве кодировки сервера.
Перезапустите %s выбрав другую локаль.
 Введите его снова:  Введите новый пароль администратора:  Если вы хотите создать новую систему баз данных, удалите либо всю 
директорию "%s" или её содержимое или выполните %s
с аргументом отличным от "%s".
 Если вы действительно хотите хранить журнал транзакций здесь, удалите
директорию "%s" либо всё её содержимое.
 Пароли не совпадают.
 Перезапустите %s с опцией -E.
 Выполнение в режиме отладки.
 Выполнение в режиме 'noclean'.  Сборка мусора и чистка после ошибок производиться не будет.
 Кластер баз данных будет инициализирован с локалью %s.
 Кластер баз данных будет инициализирован со следующими локалями:
  COLLATE:  %s
  CTYPE:    %s
  MESSAGES: %s
  MONETARY: %s
  NUMERIC:  %s
  TIME:     %s
 Кодировка базы по умолчанию установлена в %s.
 Конфигурация полнотекстового поиска по умолчанию установлена в "%s".
 Кодировка которую вы выбрали (%s) и кодировка выбранной
локали (%s) не совпадают.  Это может привести к неожиданным
результатам в различных функциях связанных с обработкой строк. 
Для исправления  перезапустите %s и, либо не указывайте
кодировку, либо задайте правильную комбинацию кодировки и локали.
 Файлы, сопутствующие этой системе баз данных, будут
принадлежать пользователю "%s". Этот пользователь
также должен быть владельцем процесса сервера.
 Программа "postgres" нужна для %s, но она не найдена в 
той же директории, что и "%s".
Проверьте вашу установку.
 Программа "postgres" найдена рядом с %s, но не
с той же версией как %s.
Проверьте вашу установку.
 Это означает, что у вас проблемы с установкой или указана
неправильная директория в опции запуска -L.
 Наберите "%s --help" для более подробной информации.
 Использование:
 перехвачен сигнал
 дочерний процесс завершился с кодом возврата %d дочерний процесс завершился с нераспознанным статусом %d дочерний процесс завершён исключением 0x%X дочерний процесс завершён сигналом %d дочерний процесс завершён сигналом %s копирование template1 в postgres ...  копирование template1 в template0 ...  не удалось поменять директорию на "%s" "%s" не найден для выполнения не удалось идентифицировать текущую директорию: %s не удалось открыть директорию "%s": %s
 не удалось считать бинарный "%s" не удалось прочитать директорию "%s": %s
 не удалось считать символическую ссылку "%s" не удалось удалить файл или директорию "%s": %s
 не удалось создать связь для "%s": %s
 не удалось получить статус файла или директории "%s": %s
 не удалось записать в дочерний процесс: %s
 создание конфигурационных файлов ...  создание конверсий ...  создание словарей ...  создание директории %s ...  создание информационной схемы ...  создание поддиректорий ...  создание системных представлений ...  создание базы template1 в %s/base/1 ...  исправление прав на существующую директорию %s ...  инициализация зависимостей ...  инициализация pg_authid ...  неверный бинарный "%s" загружется PL/pgSQL язык на стороне сервера ...  загрузка системных описаний объектов ...  ок
 нехватка памяти
 выбирается значение по умолчанию для max_connections ...  выбирается значение по умолчанию для shared_buffers ...  установка пароля ...  установка привилегий для встроенных объектов ...  сборка мусора в базе template1 ...  