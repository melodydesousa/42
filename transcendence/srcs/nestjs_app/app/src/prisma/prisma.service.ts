import { Injectable, OnModuleDestroy, OnModuleInit } from '@nestjs/common';
import { PrismaClient } from "@prisma/client";
import { ConfigService } from "@nestjs/config";

@Injectable()
export class PrismaService extends PrismaClient implements OnModuleInit, OnModuleDestroy {
	constructor(_config: ConfigService) {
		super({
			datasources: {
				db: {
					url: _config.get('DATABASE_URL')
				}
			}
		});
	}
	// Clean the whole db, $transaction garantees that it is executed in specified order
	cleanDb() {
		return this.$transaction([
			this.bookmark.deleteMany(),
			this.user.deleteMany()
		])
	}

	async onModuleDestroy(): Promise<any> {
		await this.$disconnect()
	}

	async onModuleInit(): Promise<any> {
		await this.$connect()
	}
}
