FROM 	debian:buster
RUN 	apt update && \
	apt install nginx -y && \
	apt install vim -y && \
	apt install curl -y && \
	mkdir -p /etc/nginx/ssl && \
	apt install openssl -y && \
	openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Paris/0=42/OU=42/CN=mede-sou.42.fr/UID=mede-sou" && \
	mkdir -p /var/run/nginx && \
	chmod 755 /var/www/html && \
	chmod -R www-data:www-data /var/www/html
COPY 	conf/nginx.conf /etc/nginx/nginx.conf
CMD	[ "nginx", "-g", "daemon off;" ]
