��    m      �  �   �      @	      A	     b	  &   t	     �	     �	  -   �	     
  =   
     \
  |   y
     �
  a     K   x     �  A   �  !   !  3   C  ?   w  ?   �  H   �  D   @  E   �  ?   �  >     9   J  B   �  <   �  �     0   �  F   �  >     8   @  2   y  O   �  7   �     4     ;  �   D  !   �  C   �  y   ;  C   �  D   �  >   >  A   }  *   �  /   �  %     /   @  #   p     �  3   �  0   �  ,     .   D  3   s  -   �  0   �  5     *   <  "   g  $   �  J   �     �       3   -  0   a     �     �  !   �  $   �        -   ,  4   Z  %   �  $   �  "   �  F   �  F   D     �  7   �  )   �  k     `   m  %   �  &   �       d   #     �  &   �  0   �  .   �  )   .  )   X  "   �      �  (   �     �  !   
     ,     @     V     g     w     �     �  "   �     �  �  �  )   �     �  2   �  6      8   J   <   �      �   H   �   *   !  �   H!  '   �!  Y   �!  Z   W"  "   �"  F   �"  !   #  7   >#  >   v#  ;   �#  D   �#  J   6$  Q   �$  5   �$  N   	%  2   X%  f   �%  ?   �%  �   2&  2   �&  O   '  G   c'  3   �'  5   �'  h   (  E   ~(     �(     �(  �   �(  "   �)  T   �)  �   )*  T   �*  P   +  G   g+  N   �+  +   �+  9   *,  '   d,  ,   �,  $   �,     �,  -   �,  ;   *-  4   f-  5   �-  ;   �-  0   .  0   >.  .   o.  .   �.  (   �.  &   �.  S   /      q/     �/  1   �/  7   �/     0     ,0  $   D0  ,   i0  "   �0  @   �0  7   �0     21      R1     s1  b   �1  X   �1     O2  A   i2  ,   �2  ~   �2  z   W3  &   �3  ?   �3     94  m   G4  $   �4  :   �4  ;   5  =   Q5  9   �5  9   �5  /   6  '   36  #   [6  '   6      �6     �6     �6     �6     7     /7     B7     U7  "   u7  #   �7               6      7         =          [           )      :   /   $          f           (   a   T   Y   M   >   _   g      D   F   '       R   J          .   &              k      8       U   ;                N   I   C   b   5      E               +       \   L   	   V          e          
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
 waiting for server to shut down... waiting for server to start... Project-Id-Version: pg_ctl-tr
Report-Msgid-Bugs-To: pgsql-bugs@postgresql.org
POT-Creation-Date: 2010-08-31 20:08+0000
PO-Revision-Date: 2010-09-01 11:15+0200
Last-Translator: Devrim GÜNDÜZ <devrim@gunduz.org>
Language-Team: Turkish <ceviri@postgresql.org.tr>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.9.1
X-Poedit-Language: Turkish
X-Poedit-Country: TURKEY
 
kill için izin verilen sinyal adları:
 
Ortak seçenekler:
 
Kaydetmek ya da kaydı silmek için seçenekler:
 
Başlamak ya da yeniden başlamak için seçenekler:
 
Başlatmak ya da yeniden başlatmak için seçenekler:
 
Hataları <pgsql-bugs@postgresql.org> adresine bildiriniz.
 
Kapatma modları:
   %s init[db]              [-D VERİ_DİZİNİ] [-s] [-o "SEÇENEKLER"]
   %s kill    SİNYAL_ADI SÜREÇ_NUMARASI
   %s register   [-N servis adı] [-U kullanıcı adı] [-P şifre] [-D veri dizini]
                    [-w] ]-t saniye] [-o "seçenekler"]
   %s reload  [-D VERİ_DİZİNİ] [-s]
   %s restart [-w] [-t saniye] [-D veri dizini] [-s] [-m kapatma modu] [-o "seçenekler"]
   %s start   [-w] [-t saniye] [-D VERİ_DİZİNİ] [-s] [-l DOSYA_ADI] [-o "SEÇENEKLER"]
   %s status  [-D VERİ_DİZİNİ]
   %s stop    [-W] [-t saniye] [-D veri dizini] [-s] [-m kapatma modu]
   %s unregister [-N SERVİS_ADI]
   --help                 Bu yardımı göster ve çık
   --version             sürüm numarasını yazar ve çıkar
   -D, --pgdata VERİ_DİZİNİ   verinin tutulacağı alan
   -N SERVICENAME  PostgreSQL sunucusunu kaydedeceğiniz servis adı
   -P PASSWORD     PostgreSQL sunucusunu kaydetmek için hesabın şifresi
   -U USERNAME     PostgreSQL sunucusunu kaydetmek için gerekli kullanıcı adı
   -W                     işlem bitene kadar bekleme
   -c, --core-files       postgres'in core dosyaları oluşturmasına izin ver
   -c, --core-files       bu platformda uygulanmaz
   -l, --log DOSYA_ADI      Sunucu loglarını DOSYA_ADI dosyasına yaz (ya da dosyanın sonuna ekle).
   -m KAPANMA-MODU   "smart", "fast", veya "immediate" olabilir
   -o SEÇENEKLER             postgres'e (PostgreSQL sunucusu çalıştırılabilir dosyası)
                         ya da initdb'ye geçilecek komut satırı seçenekleri
   -p PATH-TO-POSTGRES  normalde gerekli değildir
   -s, --silent           sadece hataları yazar, hiç bir bilgi mesajı yazmaz
   -t SECS                -w seçeneğini kullanırken beklenecek süre
   -w                     işlem bitene kadar bekle
   fast        düzgünce kapanmadan direk olarak dur
   immediate   tam bir kapanma gerçekleşmeden dur; yeniden başladığında kurtarma modunda açılır
   smart       tüm istemciler bağlantılarını kestikten sonra dur
  tamam
  başarısız oldu
 %s başlatmak, durdurmak, yeniden başlatmak, yapılandırma dosyalarını yeniden yüklemek
PostgreSQL sunucusunun durumunu bildirmek, ya da PostgreSQL sürecini öldürmek için bir yardımcı programdır

 %s: "%s" PID dosyası bulunamadı
 %s: başka bir sunucu çalışıyor olabilir; yine de başlatmaya çalışılıyor.
 %s: root olarak çalıştırılamaz
Lütfen  (yani "su" kullanarak) sunucu sürecine sahip olacak (yetkisiz) kullanıcı
ile sisteme giriş yapınız.
 %s: sunucu yeniden yüklenemedi, tek kullanıcılı sunucu çalışıyor (PID: %ld)
 %s: sunucu başlatılamadı; tek kullanıcılı sunucu çalışıyor (PID: %ld)
 %s: core boyutu ayarlanamadı; hard limit tarafından sınırlanmış.
 %s: sunucu durdurulamadı; tek kullanıcılı sunucu çalışıyor (PID: %ld)
 %s:Çalıştırılabilir dosya bulunamadı
 %s: çalıştırılabilir postgres programı bulunamadı
 %s: "%s" PID dosyası açılamadı: %s
 %s: "%s" servisi açılamadı: Hata kodu %d
 %s: servis yöneticisi açılamadı
 %s: "%s" dosyası okunamadı
 %s: "%s" servisi kaydedilemedi: Hata kodu %d
 %s: yeniden yükleme sinyali gönderilemedi (PID: %ld): %s
 %s: %d reload sinyali gönderilemedi (PID: %ld): %s
 %s:durdurma sinyali başarısız oldu (PID: %ld): %s
 %s: sunucu başlatılamadı
Kayıt dosyasını inceleyiniz
 %s: sunucu başlatılamadı: çıkış kodu: %d
 %s: "%s" servisi başlatılamadı: Hata kodu %d
 %s:  "%s" servisi kaydedilemedi: Hata kodu %d
 %s: veritabanı ilklendirme başarısız oldu
 %s: "%s" PID dosyasında geçersiz veri
 %s: kill modu için eksik argümanlar
 %s: Hiçbir veritabanı dizini belirtilmemiş ve PGDATA çevresel değişkeni boş
 %s: hiçbir işlem belirtilmedi
 %s: çalışan sunucu yok
 %s: eski sunucu süreci (PID: %ld) kaybolmuştur
 %s: "%s" seçenek dosyası sadece 1 satır olmalıdır
 %s: yetersiz bellek
 %s: sunucu kapanmıyor
 %s: sunucu çalışıyor (PID: %ld)
 %s: "%s" servisi daha önce kaydedilmiştir
 %s: "%s" servisi kayıtlı değil
 %s: sunucu, tek kullanıcı biçiminde çalışıyor (PID: %ld)
 %s: çok fazla komut satırı argümanı (ilki : "%s")
 %s: geçersiz işlem modu "%s"
 %s: geçersiz kapanma modu "%s"
 %s: geçersiz sinyal adı "%s"
 (Ön tanımlı işlem kapanmak için beklemektir;  başlamak ya da yeniden başlamak değildir.)

 Eğer -D seçeneği gözardı edilirse, PGDATA çevresel değişkeni kullanılacaktır.
 sunucu çalışıyor mu?
 Lütfen tek kullanıcılı sunucuyu durdurun ve yeniden deneyin.
 Sunucu başladı ve bağlantı kabul ediyor
 "%s" programına %s tarafından gereksinim duyuluyor, ancak 
"%s" ile aynı dizinde bulunamadı.
Kurulumunuzu kontrol ediniz.
 "%s" programı "%s" tarafından
bulundu ancak %s ile aynı sürüm numarasına sahip değil.
Kurulumunuzu kontrol ediniz.
 Sunucu başlarken zaman aşımı oldu
 Daha fazla bilgi için "%s --help" komutunu kullanabilirsiniz.
 Kullanımı:
 WARNING: çevrimiçi yedekleme modu etkin
pg_stop_backup() çalıştırılmadam sunucu kapatılmayacaktır.

 Sunucunun başlaması bekleniyor...
 alt süreç %d çıkış koduyla sonuçlandırılmıştır alt süreç %d bilinmeyen durumu ile sonlandırılmıştır alt süreç 0x%X exception tarafından sonlandırılmıştır alt süreç %d sinyali tarafından sonlandırılmıştır alt süreç %s sinyali tarafından sonlandırılmıştır çalışma dizini "%s" olarak değiştirilemedi "%s"  çalıştırmak için bulunamadı geçerli dizin tespit edilemedi: %s "%s" ikili (binary) dosyası okunamadı symbolic link "%s" okuma hatası geçersiz ikili (binary) "%s" sunucu kapatılıyor
 sunucuya sinyal gönderildi
 sunucu başlatıldı
 sunucu başlıyor
 sunucu durduruldu
 sunucu yine de başlatılıyor
 sunucunun kapanması bekleniyor... sunucunun başlaması bekleniyor... 