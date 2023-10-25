/*
  Warnings:

  - Added the required column `friendId` to the `friends` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
CREATE SEQUENCE friends_id_seq;
ALTER TABLE "friends" ADD COLUMN     "friendId" INTEGER NOT NULL,
ALTER COLUMN "id" SET DEFAULT nextval('friends_id_seq');
ALTER SEQUENCE friends_id_seq OWNED BY "friends"."id";
