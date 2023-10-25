-- AlterTable
ALTER TABLE "users" ADD COLUMN     "avatar" TEXT NOT NULL DEFAULT './default_path/avatar.png',
ADD COLUMN     "isonline" BOOLEAN NOT NULL DEFAULT true;
