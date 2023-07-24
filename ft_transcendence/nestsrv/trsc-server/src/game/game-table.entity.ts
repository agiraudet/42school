import { Exclude } from "class-transformer";
import { User } from "src/auth/user.entity";
import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";


@Entity()
export class GameTable {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @ManyToOne(() => User, user => user.gameTable)
    @Exclude({toPlainOnly: true}) 
    user: User;

    @Column()
    isWinner: boolean;

    @Column()
    points: number;

    @Column()
    opponent: string;

    @Column()
    scoreUser: number;

    @Column()
    scoreOpponent: number;
}