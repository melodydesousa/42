/*
  Warnings:

  - A unique constraint covering the columns `[opponentId]` on the table `games` will be added. If there are existing duplicate values, this will fail.

*/
-- DropForeignKey
ALTER TABLE "games" DROP CONSTRAINT "games_opponentId_fkey";

-- AlterTable
ALTER TABLE "games" ALTER COLUMN "opponentId" DROP NOT NULL,
ALTER COLUMN "opponentId" DROP DEFAULT;
DROP SEQUENCE "games_opponentId_seq";

-- CreateIndex
CREATE UNIQUE INDEX "games_opponentId_key" ON "games"("opponentId");

-- AddForeignKey
ALTER TABLE "games" ADD CONSTRAINT "games_opponentId_fkey" FOREIGN KEY ("opponentId") REFERENCES "users"("id") ON DELETE SET NULL ON UPDATE CASCADE;
