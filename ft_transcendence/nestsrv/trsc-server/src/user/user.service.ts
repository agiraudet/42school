import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Friend } from './friend.entity';
import { FriendRepository } from './friend.repository';
import { BlockList } from 'net';
import { BlockRepository } from './block.repository';
import { UserRepository } from 'src/auth/user.repository';
import { AddFriendDto } from './dto/add-friend.dto';
import { User } from 'src/auth/user.entity';
import { AddBlockDto } from './dto/add-block.dto';
import { setDefaultResultOrder } from 'dns';
import { GetFriendsFilterDto } from './dto/get-friend.dto';

@Injectable()
export class UserService {
  constructor(
    @InjectRepository(UserRepository)
    private userRepository: UserRepository,
    @InjectRepository(FriendRepository)
    private friendRepository: FriendRepository,
    @InjectRepository(BlockRepository)
    private blockRepository: BlockRepository,
  ) { }

  async addFriend(addFriendDto: AddFriendDto, user: User) {
    const userFriend = addFriendDto;
    const friend = await this.userRepository.findOneBy({ username: userFriend.username });
    if (!friend) {
      throw new NotFoundException('This person does not exist');
    }
    return await this.friendRepository.addFriend(friend, user);
  }

  async getIdByUsername(username: string): Promise<string> {
    const user = await this.userRepository.findOneBy({ username: username });
    if (!user) {
      return '';
    }
    return user.id;
  }


  async addBlock(addBlockDto: AddBlockDto, user: User) {
    const userBlock = addBlockDto;
    const block = await this.userRepository.findOneBy({ username: userBlock.username });
    if (!block) {
      throw new NotFoundException('This person does not exist');
    }
    return await this.blockRepository.addBlock(block, user);
  }

  async deleteFriendByUsername(username: string, user: User) {
    return this.friendRepository.deleteFriendById(await this.getIdByUsername(username), user);
  }

  deleteFriendById(id: string, user: User) {
    return this.friendRepository.deleteFriendById(id, user);
  }

  deleteBlockById(id: string, user: User) {
    return this.blockRepository.deleteBlockById(id, user);
  }

  getFriends(filterDto: GetFriendsFilterDto, user: User) {
    const { status } = filterDto;
    return this.friendRepository.getFriends(status, user);
  }

  getAllFriends(user: User) {
    return this.friendRepository.getAllFriends(user);
  }

  getBlocklist(user: User) {
    return this.blockRepository.getBlocks(user);
  }
}
