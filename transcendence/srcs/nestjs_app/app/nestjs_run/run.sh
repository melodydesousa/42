#!/bin/sh
# Function to run Prisma migration
run_migration() {
  npx prisma migrate deploy
}

# Try running the migration until it succeeds
while ! run_migration; do
 echo "Migration failed. Retrying in 5 seconds..."
 sleep 5
done
echo "Migration succeeded!" | tee -a .migration_done | xargs echo
# insert fictive users:
#node ../app/prisma/seed.ts
yarn start run --watch
