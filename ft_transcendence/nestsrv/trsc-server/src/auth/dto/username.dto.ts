import { IsAlphanumeric, IsOptional, IsString, MaxLength, MinLength } from "class-validator";


export class UsernameDto {
    @IsString()
    @MinLength(4)
    @MaxLength(20)
    @IsAlphanumeric()
    username: string;
}