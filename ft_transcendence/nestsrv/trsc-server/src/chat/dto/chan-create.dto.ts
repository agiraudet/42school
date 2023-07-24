import { ApiProperty } from "@nestjs/swagger";
import { IsString, MaxLength, MinLength } from "class-validator";

export class ChanCreateDto {
    @ApiProperty()
    @IsString()
    name: string;

    @ApiProperty()
    @IsString()
    status: string;
    
    @ApiProperty()
    @IsString()
    owner: string;

    @ApiProperty()
    @IsString()
    password: string;
}