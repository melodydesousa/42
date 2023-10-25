import { createParamDecorator, ExecutionContext } from '@nestjs/common';

export const _GetUser = createParamDecorator((data: string | undefined, ctx: ExecutionContext) => {
	const _request: Express.Request = ctx.switchToHttp().getRequest();
	if (data) {
		return _request.user[data]
	}
	else
		return _request.user
})