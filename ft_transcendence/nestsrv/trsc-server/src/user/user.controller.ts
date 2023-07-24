import { Body, Controller, Delete, Get, Param, Post, Query, Res, UseGuards } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { UserService } from './user.service';
import { AddFriendDto } from './dto/add-friend.dto';
import { GetUser } from 'src/auth/get-user.decorator';
import { User } from 'src/auth/user.entity';
import { Friend } from './friend.entity';
import { AddBlockDto } from './dto/add-block.dto';
import { Block } from './block.entity';
import { GetFriendsFilterDto } from './dto/get-friend.dto';
import { FriendListDto } from './dto/friend-list.dto';
import { UserStatus } from './user-status.enum';
import { join } from 'path';

@Controller('user')
@UseGuards(AuthGuard())
export class UserController {
    constructor(private userService: UserService) {}

    @Post('/addFriend')
    addFriend(@Body() addFriendDto: AddFriendDto,
                @GetUser() user: User): Promise<Friend>
    {
        return this.userService.addFriend(addFriendDto, user);
    }

    @Delete('/delete-friend/:username')
    deleteFriendById(@Param('username') username: string, @GetUser() user: User) 
    {
        return this.userService.deleteFriendByUsername(username, user);
    }

    @Get('/isfriend/:username')
    async isFriend(
        @GetUser() user: User,
        @Param('username') username: string
    ) {
        const friendList = await this.userService.getAllFriends(user);
        const index = friendList.findIndex((friend) => friend.username === username);
        return (index >= 0);
    }

    @Get('/friendlist')
    getFriends(@Query() filterDto: GetFriendsFilterDto, 
                @GetUser() user: User)
    {
        return this.userService.getFriends(filterDto, user);
    }

    @Get('/friendsstatus')
    async getFriendsStatus(@GetUser() user: User) : Promise<FriendListDto[]>
    {
        let friendList: FriendListDto[] = [];
        // const online: User[] = await this.userService.getFriends({status: UserStatus.ONLINE}, user);
        // const offline: User[] = await this.userService.getFriends({status: UserStatus.OFFLINE}, user);
        // const ingame: User[] = await this.userService.getFriends({status: UserStatus.IN_GAME}, user);
        const flist = await this.userService.getAllFriends(user);
        for (const f of flist) {
            switch (f.userStatus) {
                case UserStatus.IN_GAME:
                    friendList.push({name: f.username, status:'ingame'});
                    break;
                case UserStatus.OFFLINE:
                    friendList.push({name: f.username, status:'offline'});
                    break;
                case UserStatus.ONLINE:
                    friendList.push({name: f.username, status:'online'});
                    break;
            }
        }

        // for (const friend of online) {
        //     friendList.push({name: friend.username, status:'online'});
        // }
        // for (const friend of offline) {
        //     friendList.push({name: friend.username, status:'offline'});
        // }
        // for (const friend of ingame) {
        //     friendList.push({name: friend.username, status:'ingame'});
        // }

        return friendList;

    }
}


@Controller('block')
@UseGuards(AuthGuard())
export class BlockController {
    constructor(private userService: UserService) {}

    @Post('/addBlock')
    addBlock(@Body() addBlockDto: AddBlockDto,
                @GetUser() user: User): Promise<Block>
    {
        return this.userService.addBlock(addBlockDto, user);
    }

    @Delete('/delete-block/:id')
    deleteBlockById(@Param('id') id: string, @GetUser() user: User)
    {
        return this.userService.deleteBlockById(id, user);
    }

    @Get('/blocklist')
    getBlocklist(@GetUser() user: User)
    {
        return this.userService.getBlocklist(user);
    }
}
