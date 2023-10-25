FROM    node:18-alpine3.15

RUN     set -x && \
		mkdir -p /app

WORKDIR /app
COPY    . .

RUN		npm install

COPY    reactjs_run/run.sh .

RUN     chmod +x ./run.sh

ENTRYPOINT	["sh", "/app/run.sh"]
