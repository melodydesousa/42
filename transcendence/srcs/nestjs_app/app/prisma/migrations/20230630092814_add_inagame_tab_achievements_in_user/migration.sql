/*
  Warnings:

  - The `achievement` column on the `users` table would be dropped and recreated. This will lead to data loss if there is data in the column.

*/
-- AlterTable
ALTER TABLE "users" ADD COLUMN     "isingame" BOOLEAN NOT NULL DEFAULT false,
DROP COLUMN "achievement",
ADD COLUMN     "achievement" TEXT[];
