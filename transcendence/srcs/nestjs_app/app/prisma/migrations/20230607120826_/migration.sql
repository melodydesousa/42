/*
  Warnings:

  - You are about to drop the column `opponent` on the `games` table. All the data in the column will be lost.

*/
-- AlterTable
ALTER TABLE "games" DROP COLUMN "opponent",
ADD COLUMN     "opponentId" SERIAL NOT NULL;

-- AddForeignKey
ALTER TABLE "games" ADD CONSTRAINT "games_opponentId_fkey" FOREIGN KEY ("opponentId") REFERENCES "users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;
