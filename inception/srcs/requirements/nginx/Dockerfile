FROM 	debian:buster
RUN 	apt update
RUN	apt install nginx -y
RUN	apt install vim -y
RUN	apt install curl -y
RUN	apt install openssl -y
RUN	mkdir -p /etc/nginx/ssl

COPY 	./conf/default /etc/nginx/sites-enabled/default

RUN	openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Paris/0=42/OU=42/CN=mede-sou.42.fr/UID=mede-sou"

RUN	mkdir -p /var/run/nginx
RUN	chmod 777 /var/www/html
RUN	chown -R www-data:www-data /var/www/html
ENTRYPOINT	["nginx", "-g", "daemon off;"]
