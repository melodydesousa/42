/*
  Warnings:

  - You are about to drop the column `opponentId` on the `games` table. All the data in the column will be lost.
  - Added the required column `opponent` to the `games` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "games" DROP CONSTRAINT "games_opponentId_fkey";

-- DropIndex
DROP INDEX "games_opponentId_key";

-- AlterTable
ALTER TABLE "games" DROP COLUMN "opponentId",
ADD COLUMN     "opponent" TEXT NOT NULL,
ALTER COLUMN "score" DROP DEFAULT,
ALTER COLUMN "score" SET DATA TYPE TEXT;
