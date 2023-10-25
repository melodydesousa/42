import { AppModule } from "../src/app.module";
import { Test, TestingModule } from "@nestjs/testing";
import * as _pactum from 'pactum'
import { HttpStatus, INestApplication, ValidationPipe } from "@nestjs/common";
import { PrismaService } from "../src/prisma/prisma.service";
import { AuthDto } from "../src/auth/dto";
import { EditUserDto } from "../src/user/dto";
import { CreateBmDto, EditBmDto } from "../src/bookmark/dto";

describe('App e2e', () => {
	let _app: INestApplication
	let _prisma: PrismaService
	beforeAll(async () => {
		const _moduleRef: TestingModule = await Test.createTestingModule({
			imports: [AppModule],
		}).compile()
		_app = _moduleRef.createNestApplication()
		_app.useGlobalPipes(new ValidationPipe({
			whitelist: true,
		}))
		await _app.init()
		await _app.listen(3333)
		_prisma = _app.get(PrismaService)
		await _prisma.cleanDb()
		const host = process.env.REACT_APP_HOST
		_pactum.request.setBaseUrl(`http://${host}:3332`)
	})
	afterAll(() => {
		_app.close()
	})
	describe('Auth', () => {
		const _dto: AuthDto = {
			email: 'TESTtn@live.fr',
			password: 'TESThaha123',
			nickname: 'ZeBoss'
		}
		describe('Signup', () => {
			it('up should throw if email empty', () => {
				return _pactum
					.spec()
					.post('/auth/local/signup')
					.withBody({ _password: _dto.password })
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('up should throw if password empty', () => {
				return _pactum
					.spec()
					.post('/auth/local/signup')
					.withBody({ _email: _dto.email })
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('up should throw if no body', () => {
				return _pactum
					.spec()
					.post('/auth/local/signup')
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('should signup', () => {
				// append .inspect() to inspect return
				return _pactum
					.spec()
					.post('/auth/local/signup')
					.withBody(_dto)
					.expectStatus(HttpStatus.CREATED)
			})
			it('up should throw if duplicate email', () => {
				return _pactum
					.spec()
					.post('/auth/local/signup')
					.withBody(_dto)
					.expectStatus(HttpStatus.FORBIDDEN)
			})
		});
		describe('Sign In', () => {
			it('in should throw if email empty', () => {
				return _pactum
					.spec()
					.post('/auth/local/signin')
					.withBody({ _password: _dto.password })
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('in should throw if password empty', () => {
				return _pactum
					.spec()
					.post('/auth/local/signin')
					.withBody({ _email: _dto.email })
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('in should throw if no body', () => {
				return _pactum
					.spec()
					.post('/auth/local/signin')
					.expectStatus(HttpStatus.BAD_REQUEST)
			})
			it('should signin', () => {
				// append .inspect() to inspect return
				return _pactum
					.spec()
					.post('/auth/local/signin')
					.withBody(_dto).expectStatus(HttpStatus.OK)
					.stores('_userAT', 'access_token')
			})
		});
	});
	describe('User', () => {
		describe('Get me', () => {
			it('should NOT get current user', () => {
				return _pactum
					.spec().get('/users/me')
					.expectStatus(HttpStatus.UNAUTHORIZED)
			})
			it('should get current user', () => {
				return _pactum
					.spec()
					.get('/users/me')
					.withHeaders({ Authorization: 'Bearer $S{_userAT}' })
					.expectStatus(HttpStatus.OK).inspect()
			})
		});
		describe('Edit me', () => {
			it('should edit the user', () => {
				const _dto: EditUserDto = {
					firstname: 'jean bon',
					email: 'edit@edit.fr',
				}
				return _pactum.spec()
					.patch('/users')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}',
					})
					.withBody(_dto)
					.expectStatus(HttpStatus.OK)
					.expectBodyContains(_dto.email)
					.expectBodyContains(_dto.firstname)
			})
		});
	});
	describe('Bookmarks', () => {
		describe('Get empty BM', () => {
			it('sould return empty BM', () => {
				return _pactum
					.spec()
					.get('/bookmarks')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}',
					})
					.expectStatus(HttpStatus.OK)
					.expectBody([])
			})
		})
		describe('Create bm', () => {
			const _dto: CreateBmDto = {
				title: 'this one tutorial',
				description: 'the tutorial about nestjs',
				link: 'https://www.youtube.com/watch?v=GHTA143_b-s'
			}
			it('sould create BM', () => {
				return _pactum
					.spec()
					.post('/bookmarks/create')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}'
					})
					.withBody(_dto)
					.expectStatus(HttpStatus.CREATED)
					.stores('_bmId', 'id')
			})
		})
		describe('Get all BM', () => {
			it('sould return all BM', () => {
				return _pactum
					.spec()
					.get('/bookmarks')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}',
					})
					.expectStatus(HttpStatus.OK)
					.expectJsonLength(1)
			})
		})
		describe('Get bm by id', () => {
			it('should get BM by id', () => {
				return _pactum
					.spec()
					.get('/bookmarks/{id}')
					.withPathParams('id', '$S{_bmId}')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}',
					})
					.expectStatus(HttpStatus.OK)
					.expectBodyContains('$S{_bmId}')
			})
		})
		describe('Edit bm by id', () => {
			it('should edit BM by id', () => {
				const _dto: EditBmDto = {
					title:
						'NestJs Course for Beginners - Create a REST API',
					description:
						'Learn NestJs by building a CRUD REST API with end-to-end tests using modern web development techniques. NestJs is a rapidly growing node js framework that helps build scalable and maintainable backend applications.'
				}
				return _pactum
					.spec()
					.patch('/bookmarks/{id}')
					.withPathParams('id', '$S{_bmId}')
					.withHeaders({
						Authorization: 'Bearer $S{_userAT}',
					})
					.withBody(_dto)
					.expectStatus(HttpStatus.OK)
					.expectBodyContains(_dto.title)
					.expectBodyContains(_dto.description)
			})
		})
		//   describe('Delete bm by id', () => {
		//     it('should delete a BM by id', () => {
		//       return _pactum
		// 	      .spec()
		// 	      .delete('/bookmarks/{id}')
		// 	      .withPathParams('id', '$S{_bmId}')
		// 	      .withHeaders({
		// 		      Authorization: 'Bearer $S{_userAT}',
		// 	      })
		// 	      .expectStatus(HttpStatus.NO_CONTENT)
		// 	      .inspect()
		//     })
		//   })
		// describe('Get empty BM', () => {
		//   it('sould return empty BM', () => {
		// 	  return _pactum
		// 		  .spec()
		// 		  .get('/bookmarks')
		// 		  .withHeaders({
		// 			  Authorization: 'Bearer $S{_userAT}',
		// 		  })
		// 		  .expectStatus(HttpStatus.OK)
		// 		  .expectBody([])
		// 		  .expectJsonLength(0)
		//   })
		// })
	})
})