import { Module } from '@nestjs/common';
import { AuthModule } from "./auth/auth.module";
import { UserModule } from './user/user.module';
import { BookmarkModule } from './bookmark/bookmark.module';
import { PrismaModule } from './prisma/prisma.module';
import { ConfigModule } from "@nestjs/config";
import { APP_GUARD } from '@nestjs/core';
import { _jwtGuard } from './auth/guard';
import { ChatModule } from "./chat/chat.module";
import { GameModule } from './game/game.module';
import { FriendModule } from './friend/friend.module';
import { ServeStaticModule } from '@nestjs/serve-static/dist/serve-static.module';
 import { join } from 'path';
import {MessagesModule} from "./messages/messages.module";

@Module({
	imports: [
		ServeStaticModule.forRoot({
			rootPath: join(__dirname, '..', 'public'),
		}),
		ConfigModule.forRoot({
			isGlobal: true,
		}),
		AuthModule,
		UserModule,
		BookmarkModule,
		ChatModule,
		FriendModule,
		PrismaModule,
		GameModule,
		MessagesModule],
	// sert a récupérer les injections de dépendence pour les reflecteur
	// le réflecteur sert a identifier si un handler a des metadata comme
	// notre custom deco @Public qui sert a dire au guard _jwtGuard
	// que le handler a des métadata qui disent isPublic et donc
	// les Guard doivent être ignoré
	providers: [
		{
			provide: APP_GUARD,
			useClass: _jwtGuard
		}
	]
})
export class AppModule { }
