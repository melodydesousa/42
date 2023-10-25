import { AuthGuard } from "@nestjs/passport";

export class _RtJwtGuard extends AuthGuard('_RtStr') {
	constructor() {
		super();
	}
}