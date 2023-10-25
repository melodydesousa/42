/*
  Warnings:

  - The `score` column on the `games` table would be dropped and recreated. This will lead to data loss if there is data in the column.

*/
-- AlterTable
ALTER TABLE "games" DROP COLUMN "score",
ADD COLUMN     "score" INTEGER NOT NULL DEFAULT 0;
