export interface IMatch { id: string, isWinner: boolean, points: number, opponent: string, scoreUser: number, scoreOpponent: number }

export class MatchStats {
  nMatch: number;
  wins: number;
  loss: number;
  winrate: number;
  maxScore: number;
  minScore: number;
  avgScore: number;
  totScore: number;
  xp: number;

  constructor() {
    this.nMatch = 0;
    this.wins = 0;
    this.loss = 0;
    this.winrate = 0;
    this.maxScore = 0;
    this.minScore = 0;
    this.avgScore = 0;
    this.totScore = 0;
    this.xp = 0;
  }

  setStat(histo: IMatch[]) {
    for (const match of histo) {
      this.nMatch++;
      if (match.isWinner) {
        this.wins++;
      }
      else {
        this.loss++
      }
      this.totScore += match.scoreUser;
      if (match.scoreUser < this.minScore || this.nMatch === 1) {
        this.minScore = match.scoreUser;
      }
      if (match.scoreUser > this.maxScore) {
        this.maxScore = match.scoreUser;
      }
      this.xp += match.points;
    }
    if (this.nMatch) {
      this.winrate = parseFloat(((this.wins / this.nMatch) * 100).toFixed(2));
      this.avgScore = parseFloat(((this.totScore / this.nMatch)).toFixed(1));
    }
  }
}
