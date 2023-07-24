import { Body, Controller, GoneException, Param, Post, UseGuards } from '@nestjs/common';
import { PongService } from './pong.service';
import { PongGateway } from './pong.gateway';
import { ApiForbiddenResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';
import { AuthGuard } from '@nestjs/passport';
import { GetUser } from 'src/auth/get-user.decorator';
import { User } from 'src/auth/user.entity';
import { RulesDto } from './dto/rules.dto';
import { Rules } from './entities/rules.entity';

@ApiTags('pong')
@Controller('pong')
@UseGuards(AuthGuard())
export class PongController {
    constructor(private pongService: PongService, private pongGateway: PongGateway) {}

    @ApiOkResponse({type: String, isArray: false})
    @ApiForbiddenResponse()
    @Post('vs/:target')
    createVsGame(
        @GetUser() user: User,
        @Param('target') target: string
      ) {
       this.pongService.addToVsWaitList(user.username, target, new Rules()); 
       return ('invited player to game');
    }

    @ApiOkResponse({type: String, isArray: false})
    @ApiForbiddenResponse()
    @Post('vs/:target/:answer')
    acceptVsGame(
        @GetUser() user: User,
        @Param('target') target: string,
        @Param('answer') answer: string
      ) {
        if (answer === 'y') {
         if (this.pongService.acceptVsGame(user.username, target)) {
          return ('accepted invite');
         }
         else {
          throw new GoneException();
         }
        }
        else {
          this.pongService.refuseVsGame(user.username, target);
        }
       return ('invite accepted');
    }
    
    @ApiOkResponse({type: String, isArray: false})
    @ApiForbiddenResponse()
    @Post('custom/:target')
    createCustomGame(
      @GetUser() user: User,
      @Param('target') target: string,
      @Body() body: RulesDto
    ): string {
      const rules = new Rules();
      rules.setRules(body);
      this.pongService.addToVsWaitList(user.username, target, rules);
      return('invited player to custom game');
    }

}
