FROM 	debian:buster
EXPOSE  9000
RUN 	apt update
RUN	    apt-get -y install wget
RUN	    apt-get install -y vim
RUN	    apt-get install -y php7.3
RUN	    apt-get install -y php-fpm
RUN	    apt-get install -y php-mysql
RUN	    apt-get install -y mariadb-client 
RUN	    wget https://fr.wordpress.org/wordpress-6.0-fr_FR.tar.gz -P /var/www
RUN	    cd /var/www && tar -xzf wordpress-6.0-fr_FR.tar.gz && rm wordpress-6.0-fr_FR.tar.gz
RUN	    chown -R root:root /var/www/wordpress
RUN	    wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN	    chmod +x wp-cli.phar
RUN	    mv wp-cli.phar /usr/local/bin/wp
RUN     mkdir -p /run/php/
COPY 	conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf
COPY 	conf/auto_config.sh /var/www/wordpress/auto_config.sh
RUN	    chmod +x /var/www/wordpress/auto_config.sh
ENTRYPOINT ["bash", "/var/www/wordpress/auto_config.sh"]
