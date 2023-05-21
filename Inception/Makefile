wordpress = /home/mede-sou/data/wordpress
mariadb = /home/mede-sou/data/mariadb

all:	| $(wordpress) $(mariadb) 
	@docker compose -f srcs/docker-compose.yml up -d --build

$(wordpress):
	@echo "Building $(wordpress)..."
	@sudo mkdir -p $@
	@sudo chmod 777 $@

$(mariadb):
	@echo "Building $(mariadb)..."
	@sudo mkdir -p $@
	@sudo chmod 777 $@

re: fclean all

run:
	@docker compose -f srcs/docker-compose.yml up -d

stop:
	@docker compose -f srcs/docker-compose.yml down

clean:  stop
	@docker compose -f srcs/docker-compose.yml down -v
	
fclean: clean 
	@sudo rm -rf /home/mede-sou/data/wordpress
	@sudo rm -rf /home/mede-sou/data/mariadb
	@docker system prune -a -f
.PHONY: stop clean fclean run all  re
