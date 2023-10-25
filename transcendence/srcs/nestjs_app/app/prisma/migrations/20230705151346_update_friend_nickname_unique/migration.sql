/*
  Warnings:

  - A unique constraint covering the columns `[nickname]` on the table `friends` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX "friends_nickname_key" ON "friends"("nickname");
