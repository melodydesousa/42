/*
  Warnings:

  - The primary key for the `friends` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - A unique constraint covering the columns `[id]` on the table `friends` will be added. If there are existing duplicate values, this will fail.

*/
-- AlterTable
ALTER TABLE "friends" DROP CONSTRAINT "friends_pkey";

-- CreateIndex
CREATE UNIQUE INDEX "friends_id_key" ON "friends"("id");
