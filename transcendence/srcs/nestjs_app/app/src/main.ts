
import { NestFactory, Reflector } from '@nestjs/core';
import { AppModule } from './app.module';
import { INestApplication, ValidationPipe } from "@nestjs/common";
import { _jwtGuard } from './auth/guard';
import * as cookieParser from 'cookie-parser';

async function bootstrap() {
	const app: INestApplication = await NestFactory.create(AppModule);
	// Validation Pipe is used to check dto format such as @IsString...
	app.use(cookieParser());
	// app.set("trust proxy", true);
	app.enableCors();
	app.useGlobalPipes(new ValidationPipe({
		whitelist: true,
	}))
	// On peut utiliser global guard mais ca ne supporte pas le dependency injection
	// donc il faut déclarer le réflecteur avant et le passer en paramètre
	// du custom guard
	// const reflector = new Reflector()
	// app.useGlobalGuards(new _jwtGuard(reflector))
	// OU BIEN on peut utiliser provider dans app.module
	await app.listen(3333);
}
bootstrap();
