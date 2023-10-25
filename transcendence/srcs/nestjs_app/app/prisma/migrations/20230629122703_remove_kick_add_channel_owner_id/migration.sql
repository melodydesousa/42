/*
  Warnings:

  - You are about to drop the column `kickList` on the `chats` table. All the data in the column will be lost.
  - The `adminId` column on the `chats` table would be dropped and recreated. This will lead to data loss if there is data in the column.
  - Added the required column `channelOwnerId` to the `chats` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "chats" DROP CONSTRAINT "chats_adminId_fkey";

-- AlterTable
ALTER TABLE "chats" DROP COLUMN "kickList",
ADD COLUMN     "channelOwnerId" INTEGER NOT NULL,
DROP COLUMN "adminId",
ADD COLUMN     "adminId" INTEGER[];

-- AddForeignKey
ALTER TABLE "chats" ADD CONSTRAINT "chats_channelOwnerId_fkey" FOREIGN KEY ("channelOwnerId") REFERENCES "users"("id") ON DELETE CASCADE ON UPDATE CASCADE;
