-- DropIndex
DROP INDEX "friends_id_key";

-- AlterTable
ALTER TABLE "friends" ADD CONSTRAINT "friends_pkey" PRIMARY KEY ("id");
