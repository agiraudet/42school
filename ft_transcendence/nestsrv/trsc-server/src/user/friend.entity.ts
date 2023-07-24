import { Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';
import { User } from '../auth/user.entity';
import { Exclude } from 'class-transformer';

@Entity()
export class Friend {
    @PrimaryGeneratedColumn('uuid')
    id: string;

    @ManyToOne(() => User, user => user.friends)
    user: User;

    @ManyToOne(() => User)
    friend: User;
}
