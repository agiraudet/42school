import { ConflictException, Injectable, NotFoundException } from "@nestjs/common";
import { DataSource, Repository } from "typeorm";
import { Block } from "./block.entity";
import { User } from "src/auth/user.entity";
import { UserStatus } from "./user-status.enum";
import { UserRepository } from "src/auth/user.repository";
import { InjectRepository } from "@nestjs/typeorm";

@Injectable()
export class BlockRepository extends Repository<Block>
{
    constructor(
        @InjectRepository(UserRepository)
        private userRepository: UserRepository,
        private dataSource: DataSource,
        )
    {
        super(Block, dataSource.createEntityManager());
    }
    
    async addBlock(newBlock: User, user : User)
    {
        const query = this.createQueryBuilder('block');
        query.where({user});
        query.andWhere("block.userId = :userId", {userId: user.id});
        query.andWhere("block.blockId = :blockId", {blockId: newBlock.id});
        const check = await query.getOne();
        if (check)
        {
            throw new ConflictException('Already blocked');
        }
        const block = this.create({
            user:   user,
            block: newBlock,
        });
        await this.save(block);
        return block;
    }
    async deleteBlockById(id: string, user: User) : Promise<void>
    {
        const check = await this.createQueryBuilder()
                                .delete()
                                .from(Block)
                                .where("userId = :userId", {userId: user.id})
                                .andWhere("blockId = :blockId", {blockId: id})
                                .execute();
        if (check.affected === 0)
            throw new NotFoundException('Not found in the blocklist');
    }

    async getBlocks(user: User) : Promise<User[]>
    {
        const query = this.createQueryBuilder('block');
        query.where({user});
        query.andWhere("block.userId = :userId", {userId: user.id});
        const blockslist = await query.getMany();
        if (!blockslist)
            throw new NotFoundException('Your blocklist is empty!');
        let blockList: User[] = [];
        for (const block of blockslist)
        {
            const usera: Block = await this.findOne({ where: { ...block }, relations: ['block'] });
            const useri : User = await this.userRepository.findOneBy(usera.block);
            blockList.push(useri);
        }
        return blockList;
    }
}