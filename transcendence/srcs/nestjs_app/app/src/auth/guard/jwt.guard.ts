import { ExecutionContext, Injectable } from "@nestjs/common";
import { Reflector } from "@nestjs/core";
import { AuthGuard } from "@nestjs/passport";


// on injecte la dépendence Reflector, l'injection est possible car 
// dans app module on donné comme provider APP_GUARD
// donc il faut aussi le déclarer comme @Ijectable
@Injectable()
export class _jwtGuard extends AuthGuard('_jwtStr') {
	constructor(private reflector: Reflector) {
		super();
	}
	// check les métadata pour trouver isPublic, si il le trouve, on return
	// true et donc le Guard est bypassé, sinon, le garde s'active
	canActivate(context: ExecutionContext) {
		// d'abord on check dans le handler: getHandler() si on le trouve pas
		// on check au niveau de la class sinon, retrun false
		const isPublic = this.reflector.getAllAndOverride('isPublic', [
			context.getHandler(),
			context.getClass()
		])
		if (isPublic)
			return true
		else
			return super.canActivate(context)
	}
}
