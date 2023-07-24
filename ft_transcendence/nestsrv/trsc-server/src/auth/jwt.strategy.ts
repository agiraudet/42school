import { Injectable, UnauthorizedException } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { InjectRepository } from "@nestjs/typeorm";
import { ExtractJwt, Strategy } from "passport-jwt";
import { UserRepository } from "./user.repository";
import { JwtPayload } from "./jwt-payload.interface";
import { User } from "./user.entity";
import { ConfigService } from "@nestjs/config";

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) // strategy should come from pwd-jwt
{
    constructor (
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private config: ConfigService,    
        ) { 
            super({
                    secretOrKey: config.get('JWT_SECRET'),
                    jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            })
        }

        async validate(payload: JwtPayload) : Promise<User> {
            const { username } = payload;
            const user = await this.userRepository.findOneBy({username: username});
            if (!user)
            {
                throw new UnauthorizedException();
            }
            return user;
        }
    }

    /*
        Passport will call the `validate()` method automatically

        My understanding is that the AuthGuard (which is provisioned by NestJS when we imported the AuthModule) in @UseGuards() executes the JWT strategy, and thus implicitly calls validate() of the strategy implementation. When we registered the PassportModule in AuthModule, we told NestJS to make "jwt" the default strategy for the module ("jwt" btw is the default name the passport-jwt strategy below NestJS is identified by). Because that module then gets exported by our AuthModule and eventually imported into our TasksModule, NestJS knows to execute the JWT strategy whenever we use AuthGuard().

Alternatively, we could have used AuthGuard("jwt") instead to explicitly determine the strategy to use with the authentication guard. This is useful in cases we have multiple different authentication strategies to work with.

In case you are wondering, how JwtStrategy "knows" that is is implementing a JWT strategy (and not some other strategy provided by different Passport modules): JWT is extending a PassportStrategy that receives a native JWT strategy (i.e. a strategy symbol exported by a native passport module such as passport-jwt) as an "argument". Therefore NestJS "knows" that JwtStrategy is implementing the strategy "jwt" of Passport.

An installed AuthGuard on a route (i.e. a controller or controller handler) is executed, when a HTTP request has arrived and just before that request is forwarded to the corresponding controller handler. If the AuthGuard decides (through its implementation) that the request is allowed to "activate" (or "pass") the request eventually is forwarded to the controller handler function, thus executing the handler function. Otherwise, the handler is not invoked and a 401 is directly returned to the requesting client instead.

    */