import { Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';
import { User } from '../auth/user.entity';
import { Exclude } from 'class-transformer';

@Entity()
export class Block {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @ManyToOne(() => User, user => user.blocks)
    @Exclude({toPlainOnly: true}) 
    user: User;

    @ManyToOne(() => User)
    @Exclude({toPlainOnly: true}) 
    block: User;
}

