import { Transform, Type } from "class-transformer";
import { IsBoolean, IsBooleanString, IsInt, IsNumber, IsString, Length } from "class-validator";

export class AddGameDto {
    @IsBoolean()
    @Type(() => Boolean)
    isWinner: boolean;

    @IsNumber()
    @Type(() => Number)  
    points: number;

    @IsString()
    @Length(4,20)
    opponent: string;

    @IsNumber()
    @Type(() => Number)
    scoreUser: number;

    @IsNumber()
    @Type(() => Number)
    scoreOpponent: number;
}