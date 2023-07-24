import { ConflictException, Injectable, NotFoundException } from "@nestjs/common";
import { DataSource, Repository } from "typeorm";
import { Friend } from "./friend.entity";
import { AddFriendDto } from "./dto/add-friend.dto";
import { User } from "src/auth/user.entity";
import { NotFoundError } from "rxjs";
import { UserStatus } from "./user-status.enum";
import { InjectRepository } from "@nestjs/typeorm";
import { UserRepository } from "src/auth/user.repository";

@Injectable()
export class FriendRepository extends Repository<Friend>
{
    constructor(
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private dataSource: DataSource,
        )
    {
        super(Friend, dataSource.createEntityManager());
    }
    
    async addFriend(newfriend: User, user : User)
    {
        const query = this.createQueryBuilder('friend');
        query.where({user});
        query.andWhere("friend.userId = :userId", {userId: user.id});
        query.andWhere("friend.friendId = :friendId", {friendId: newfriend.id});
        const check = await query.getOne();
        if (check)
        {
            throw new ConflictException('Already your friend');
        }
        const friend = this.create({
            user:   user,
            friend: newfriend,
        });
        await this.save(friend);
        return friend;
    }

    async deleteFriendById(id: string, user: User) : Promise<void>
    {
        const check = await this.createQueryBuilder()
                                .delete()
                                .from(Friend)
                                .where("userId = :userId", {userId: user.id})
                                .andWhere("friendId = :friendId", {friendId: id})
                                .execute();
        if (check.affected === 0)
            throw new NotFoundException('This Friendship does not exist');
    }

    async getFriends(status : UserStatus, user: User) : Promise<User[]>
    {
        const query = this.createQueryBuilder('friend');
        query.where({user});
        query.andWhere("friend.userId = :userId", {userId: user.id});
        const friendslist = await query.getMany();
        if (!friendslist)
            throw new NotFoundException('Your friendlist is empty!');
        let statusFriend: User[] = [];
        for (const friend of friendslist)
        {
            const usera: Friend = await this.findOne({ where: { ...friend }, relations: ['friend'] });
            const useri : User = await this.userRepository.findOneBy(usera.friend);
            if (status && useri != null && useri.userStatus == status)
                statusFriend.push(useri);
            else if (!status)
                statusFriend.push(useri);
        }
        return statusFriend;
    }

    async getAllFriends(user: User): Promise<User[]>
    {
        const query = this.createQueryBuilder('friend');
        query.where({user});
        query.andWhere("friend.userId = :userId", {userId: user.id});
        const friendslist = await query.getMany();
        if (!friendslist)
            throw new NotFoundException('Your friendlist is empty!');
        let friendList: User[] = [];
        for (const friend of friendslist)
        {
            const usera: Friend = await this.findOne({ where: { ...friend }, relations: ['friend'] });
            const useri : User = await this.userRepository.findOneBy(usera.friend);
            friendList.push(useri);
        }
        return friendList;
    }
}