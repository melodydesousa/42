import { Module } from "@nestjs/common";
import { AuthController } from "./auth.controller";
import { AuthService } from "./auth.service";
import { JwtModule } from "@nestjs/jwt";
import { JwtStrategy, RtStrategy } from "./strategy";
// import {PrismaModule} from "../prisma/prisma.module"; // inutile car module global

// Le module PrismaService est global, pas besoin de l'importer dans le decorateur Module, si pas global il faudrait
// l'importer dans tous les Modules qui en ont besoin: imports: [PrismaService],
// Attention a mettre PrismaModule dans le imports de app.module.ts par contre
@Module({
	// imports: [PrismaService],
	imports: [JwtModule.register({})],
	controllers: [AuthController],
	providers: [AuthService, JwtStrategy, RtStrategy]
})
export class AuthModule { }