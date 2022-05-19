# universal_connector
# Závislosti
## Server
- [PostgreSQL](https://www.postgresql.org/)
- [Node-RED](https://nodered.org/)
- [Eclipse Mosquitto](https://mosquitto.org/)

# Příprava serveru
Veškeré instrukce jsou platné pro Ubuntu 22.04.
## PostgreSQL
Instalace balíčků:
```console
user@server:~$ sudo apt install postgresql postgresql-contrib postgresql-client
user@server:~$ sudo systemctl enable postgresql # Spustit PostgreSQL po spuštění systému
user@server:~$ sudo systemctl start postgresql # Spustit PostgreSQL ihned
```
Nastavení PostgreSQL
```console
user@server:~$ cd /etc/postgresql/X/main # X -> verze PostgreSQL
user@server:~$ sudo cp pg_hba.conf pg_hba.conf.old # Záloha konfiguračních souborů
user@server:~$ sudo nano pg_hba.conf # Upravit přihlašování na md5 nebo scram-sha-256
user@server:~$ sudo su postgres # Přihlášení jako postgres uživatel
postgres@server:~$ psql # Vstup do postgres terminálu, následně vytvoření databáze a nastavení hesla pro postgres uživatele
psql> create database osu-tv;
      ALTER USER postgres WITH PASSWORD 'DOPLNIT';
      exit
postgres@server:~$ exit
user@server:~$ sudo systemctl restart postgresql # Restartovat službu PostgreSQL a aplikovat tak změny
```
## Mosquitto
Instalace balíčků:
```console
user@server:~$ sudo apt-get install mosquitto mosquitto-clients
user@server:~$ sudo systemctl enable mosquitto # Spustit Mosquitto po spuštění systému
user@server:~$ sudo systemctl start mosquitto # Spustit Mosquitto ihned
```
Nastavení Mosquitto
```console
user@server:~$ cd /etc/mosquitto
user@server:~$ sudo cp mosquitto.conf mosquitto.conf.old
user@server:~$ sudo nano mosquitto.conf
# Přidat/upravit v souboru následující řádky kódu:
listener 1883 0.0.0.0
allow_anonymous true
user@server:~$ sudo systemctl restart mosquitto # Aplikovat změny
```

Nastavení Node-RED
Instalace balíčků:
```console
user@server:~$ sudo apt-get install npm
user@server:~$ sudo npm install -g --unsafe-perm node-red
user@server:~$ node-red # Spustit node-red
```
Po spuštění node-red by mělo být webové rozhraní Node-RED dostupné na adrese serveru a portu č. 1880  (příklad: http://192.168.0.38:1880/)
V rozhraní Node-RED je poté nutné importovat paletu ze souboru **doc/node_red_insys_flow.json**.
To se udělá kliknutím na menu v pravém horním rohu a kliknutím na import.

<br />

![image](https://user-images.githubusercontent.com/16212013/169260462-409d9778-fc4a-4bc7-ba3d-f8a60fb3390e.png)

![image](https://user-images.githubusercontent.com/16212013/169260670-c74aa4d8-dbaa-4e8c-984a-6d1fc4efe33b.png)

## Nastavení palety
Po importování je nutné nastavit připojení palety na Mosquitto broker a PostgreSQL databázi.

### Nastavení MQTT připojení v paletě
Dvojklikněte na jakýkoliv MQTT widget a otevřte tak nabídku.

![image](https://user-images.githubusercontent.com/16212013/169260217-ab51539b-668a-4eae-b2d4-19f522838fde.png)

![image](https://user-images.githubusercontent.com/16212013/169261197-22b799cc-3f08-4ed9-8fd3-97e4624693e6.png)

Nastavte QoS na hodnotu 0 a přidejte nový server kliknutím na ikonu.
Vyplňte potřebné pole (verze MQTT musí být 3.1.1) a potvrďte volbu.
![image](https://user-images.githubusercontent.com/16212013/169262034-4b6eb644-dfa7-4218-bedc-bd4293394c51.png)

### Nastavení PostgreSQL v paletě
Dvojklikněte na jakýkoliv PostgreSQL widget a otevřte tak nabídku.

![image](https://user-images.githubusercontent.com/16212013/169263569-c16ef56f-91c2-4b4c-9339-763a3816cc60.png)

Přidejte nový server kliknutím na ikonu.

![image](https://user-images.githubusercontent.com/16212013/169263810-da7de8f2-352a-4fa3-8b07-23c684ae4d94.png)

Vyplňte potřebné pole v tabu **Connection**, **Security** a potvrďte volbu.

![image](https://user-images.githubusercontent.com/16212013/169263879-152aec3f-a300-4aa9-a3f2-602ffcf9cb5d.png)

**Po nastavení vešerých připojení je nutné aktivovat paletu kliknutím na Deploy v pravém horním rohu**

![image](https://user-images.githubusercontent.com/16212013/169265020-21761097-74dd-4a29-841d-558d15826247.png)

