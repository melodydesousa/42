FROM    node:18-alpine3.15

RUN     set -x && \
        mkdir -p /app

WORKDIR /app
COPY    app/ .

RUN    yarn install

COPY    nestjs_run/run.sh .

RUN     chmod +x ./run.sh

ENTRYPOINT	["sh", "/app/run.sh"]
