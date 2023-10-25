SRCS	=	srcs/docker-compose.yml

ENV		=	./.env

all:	up

up:
	docker-compose -f $(SRCS) up --timeout=700 --build -d

start:
	docker-compose -f $(SRCS) start

stop:
	docker-compose -f $(SRCS) stop

down:
	docker-compose -f $(SRCS) down

ps:
	docker-compose -f $(SRCS) ps

top:
	docker-compose -f $(SRCS) top

fclean:
	docker stop $$(docker ps -qa);\
    docker rm $$(docker ps -qa);\
    docker rmi -f $$(docker images -qa);\
	docker system prune -af
	docker volume prune -af

re: fclean
	all

prune:
	docker system prune -f
	docker volume prune -f

.PHONY:	all up down ps top clean fclean prune
