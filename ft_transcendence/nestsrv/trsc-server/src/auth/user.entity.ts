// import { Task } from 'src/tasks/task.entity';
import { Column, Entity, OneToMany, PrimaryGeneratedColumn } from 'typeorm';
import { UserStatus } from 'src/user/user-status.enum';
import { Friend } from 'src/user/friend.entity';
import { Block } from 'src/user/block.entity';
import { GameTable } from 'src/game/game-table.entity';
import { cp } from 'fs';

@Entity()
export class User {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @Column({unique: true})
    username: string;
    
    @Column()
    password: string;

    @Column()
    email: string;

    @Column()
    twoFactorAuthenticationSecret: string;

    @Column()
    isTwoFactorAuthenticationEnabled: boolean;

    @Column()
    isFtStudent: boolean;

    @Column()
    ftId: string;

    @OneToMany(() => Friend, friend => friend.user)
    friends: Friend[];

    @OneToMany(() => Block, block => block.user)
    blocks: Block[];

    @Column()
    avatar: string; 

    @Column()
    userStatus: UserStatus;

    @OneToMany(() => GameTable, gameTable => gameTable.user)
    gameTable: GameTable[];

    @Column()
    points: number;

    @Column()
    wins: number;

    @Column()
    loss: number;

    @Column()
    isFirstCo : boolean;
    // @OneToMany(_type => Task, (task) => task.user,{eager: true})
    // tasks: Task[];
}